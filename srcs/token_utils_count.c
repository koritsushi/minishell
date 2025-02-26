/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:05:05 by hsim              #+#    #+#             */
/*   Updated: 2025/02/26 11:47:03 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/* 
 * In general these functions & child functions counts
 * number of arguments for malloc use later
 */

/* splits current *str by *set and see if there are strings after splitting */
int	has_more_str(char *str, char *set)
{
	char	**check;
	int		res;

	res = 0;
	check = ft_split_shell(str, set);
	if (check && check[1])
	{
		res = 1;
		printf("has_more_str=%s\n", check[1]);
	}
	free_chr_ptr((void **)check);
	return (res);
}

int	has_more_str_all(char **str, char *set)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (has_more_str(str[i], set))
		{
			printf("has_more_str_all=1!\n");
			return (1);
		}
		i++;
	}
	return (0);
}

/* counts total string count in a double char array */
int	count_str_array(char **res)
{
	int	i;

	i = 0;
	while (res && res[i])
		i++;
	return (i);
}

/* gets the correct infile count for malloc use */
int	count_infile(char **res, char **infile)
{
	int	x;
	int	flag;
	int	count;

	x = 1;
	flag = 1;
	count = 0;
	if (res[0][0] == '<' && !infile[1] && has_more_str(infile[0], " \t\n\v\f\r"))
		count++;
	else if (res[0][0] != '<' && infile[1])
		count++;
	return (count);
}

/*
 * *i counts number of string combos for malloc later
 * checks if < << is at beginning, process entire line til pipe
 * if infile at middle, all strings after < are filenames
 */
int	get_malloc_size(char **res, char **infile)//, char **outfile, char *str)
{
	int		i;
	int		x;
	char	**tmp;
	char	*line;

	i = count_str_array(res); /* splitted by '|' */
	i += count_str_array(&res[1]); /*count pipes*/
	i += count_infile(res, infile);

	x = 0;
	/*count_outfiles*/
	/* if splittable*/
	while (res[x])
	{
		line = res[x];
		while (is_target(" \t\n\v\f\r", line[0]))
			line++;
		tmp = ft_split_shell(line, ">");
		printf("------\noutfile:\n");
		debug_print(tmp);

		/* cmd1 > out2 > out3 */
		/* > out1 > out2 cmd1*/
		/* > out1 cmd1 > out2*/

		
		/* > out1 > out2 > out3 */
		/* > out1 > out2, count less 1*/
		/* > out1 */

		/* if splittable '>' */
			/*if line[0] != '>', pass_all++ */
			/*if line[0] == '>' && has_more_str_all, pass_all++ */

		/* if not splittable '>' */
			/*if line[0] == '>'*/
			/*if line[0] != '>'*/

/*----------------------------------------------*/
		/* if line[0] == '>' */
			/* has_more_strs, i++ || !has_more_strs, skip */

		/* if line[0] != '>' */
		if (tmp && tmp[1])
		{
			i += count_str_array(&tmp[1]);
			if (line[0] == '>' && has_more_str_all(tmp, " \t\n\v\f\r"))
				i++;
		}
		else if (!tmp[1] && line[0] == '>' && has_more_str_all(tmp, " \t\n\v\f\r"))
			i++;
		x++;
		free_chr_ptr((void **)tmp);
	}

	// printf("------\nres:\n");
	// debug_print(res);
	// printf("------\ninfile:\n");
	// debug_print(infile);
	// printf("------\noutfile:\n");
	// debug_print(outfile);

	return (i);
}
