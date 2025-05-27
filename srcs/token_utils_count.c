/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:05:05 by hsim              #+#    #+#             */
/*   Updated: 2025/05/27 16:01:11 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* In general these functions & child functions counts
 * number of arguments for malloc use later
 * ************************************************************************** */

#include "includes/token.h"

/* counts total string count in a double char array */
int	count_str_array(char **res)
{
	int	i;

	i = 0;
	while (res && res[i])
		i++;
	return (i);
}

//24 lines!
/*
 * child function in count_infile
 * helper function to start counting
 */
static int	start_count_infile(char *str)
{
	int		x;
	int		count;
	char	**infile;
	char	**fin;

	count = 0;
	infile = ft_split_shell(str, "<");
	count += count_str_array(&infile[1]);
	//<infile in2 in3
	// cmd <in1 in2 <in3
	// cmd <<h1 in2 <in3
	// if < && any <infile has_more_str, += 1 (do once)
	x = -1;
	while (str[0] == '<' && infile[++x])
	{
		fin = ft_split_shell(infile[x], ">");
		if (str[0] == '<' && has_more_str(fin[0], " \t\n\v\f\r"))
		{
			count += 1;
			free_chr_ptr((void **)fin);
			break ;
		}
		free_chr_ptr((void **)fin);
	}
	free_chr_ptr((void **)infile);
	return (count);
}

/* 
 * child function in get_malloc_size
 * gets the correct infile count for malloc use
 */
static int	count_infile(char **res)//, char **infile)
{
	int		x;
	char	*tmp;
	int		count;

	count = 0;
	// in_fin = ft_split_shell(infile[0], ">");
	/* <in1 <in2 cmd >out | <in3 <in4 */
	// 2 types: cmd<in1 in2 | cmd<in3
	// <in1 cmd | <in2 cmd
	// if_has_str after <in1 , +1
	x = -1;
	while (res[++x])
	{
		tmp = skip_spaces(res[x], " \t\n\v\f\r");
		if (ft_strchr(tmp, '<'))
			count += start_count_infile(tmp);
	}
	return (count);
}

// 24 lines!
/*
 * child function in get_malloc_size
 * counts number of words in cmd_tail for malloc use
 * *set = set of spaces to detect: ' \t\n\v\f\r'
 */
static int	count_cmd_tail(char **res, char *set)
{
	int		i;
	int		x;
	char	**tmp;
	char	*line;

	x = 0;
	i = 0;
	while (res[x])
	{
		line = res[x];
		line = skip_spaces(line, set);
		tmp = ft_split_shell(line, ">");
		// printf("------\noutfile:\n");
		// debug_print(tmp);

		/* cmd1 > out2 > out3 */
		/* > out1 > out2 cmd1*/
		/* > out1 cmd1 > out2*/
		
		/* > out1 > out2 > out3 */
		/* > out1 */

		/* if splittable '>' */
			/* pass_all++ */
			/*if line[0] == '>' && has_more_str_all, i++ */

		/* if not splittable '>' */
			/*if line[0] == '>' && has_more_str_all, i++ */

		if (tmp && tmp[1])
		{
			i += count_str_array(&tmp[1]);
			if (line[0] == '>' && has_more_str_all(tmp, set))
				i++;
		}
		else if (!tmp[1] && line[0] == '>' && has_more_str_all(tmp, set))
			i++;
		x++;
		free_chr_ptr((void **)tmp);
	}
	return (i);
}

/*
 * *i counts number of string combos for malloc later
 * checks if < << is at beginning, process entire line til pipe
 * if infile at middle, all strings after < are filenames
 */
int	get_malloc_size(char **res)//, char **infile)
{
	int		i;
	// (void)	infile;

	/* <infile >outfile*/
	i = 0;
	i = count_str_array(res); /* splitted by '|' */
	// /*debug*/printf("------\ncount_res: %d\n", i);
	i += count_str_array(&res[1]); /*count pipes*/
	// /*debug*/printf("count_pipe: %d\n", i);
	i += count_infile(res);
	// /*debug*/printf("count_infile: %d\n", i);
	i += count_cmd_tail(res, " \t\n\v\f\r");
	// /*debug*/printf("count_cmd_tail: %d\n", i);

	// /*debug*/printf("------\nres:\n");
	// /*debug*/debug_print(res);
	// /*debug*/printf("------\ninfile:\n");
	// /*debug*/debug_print(infile);

	return (i);
}
