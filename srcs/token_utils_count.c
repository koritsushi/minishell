/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:05:05 by hsim              #+#    #+#             */
/*   Updated: 2025/03/02 08:57:54 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/* 
 * In general these functions & child functions counts
 * number of arguments for malloc use later
 */

/* counts total string count in a double char array */
static int	count_str_array(char **res)
{
	int	i;

	i = 0;
	while (res && res[i])
		i++;
	return (i);
}

/* gets the correct infile count for malloc use */
static int	count_infile(char **res, char **infile)
{
	int	x;
	int	flag;
	int	count;

	x = 1;
	flag = 1;
	count = 0;
	if (res[0][0] == '<' && !infile[1] && \
		has_more_str(infile[0], " \t\n\v\f\r"))
		count++;
	else if (res[0][0] != '<' && infile[1])
		count++;
	return (count);
}

/* counts number of chars in cmd_tail for malloc use */
int	count_cmd_tail_chr(char **outfile)
{
	int		i;
	int		len;
	char	*cmd_tail;

	i = 0;
	len = 0;
	while (outfile[i + 1])
	{
		cmd_tail = outfile[i + 1];
		cmd_tail = skip_spaces(cmd_tail, " \t\n\v\f\r");
		/* skips to the 1st space detected */
		cmd_tail = ft_strchr(cmd_tail, ' ');
		if (cmd_tail)
			len += ft_strlen(cmd_tail);
		i++;
		/*debug*/printf("otail=%s| %d+1\n", cmd_tail, len);
	}
	return (len);
}

// 24 lines!
/*
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
int	get_malloc_size(char **res, char **infile)
{
	int		i;

	i = count_str_array(res); /* splitted by '|' */
	i += count_str_array(&res[1]); /*count pipes*/
	i += count_infile(res, infile);
	i += count_cmd_tail(res, " \t\n\v\f\r");

	// printf("------\nres:\n");
	// debug_print(res);
	// printf("------\ninfile:\n");
	// debug_print(infile);
	// printf("------\noutfile:\n");
	// debug_print(outfile);

	return (i);
}
