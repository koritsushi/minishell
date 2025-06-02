/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:05:05 by hsim              #+#    #+#             */
/*   Updated: 2025/05/29 18:18:04 by hsim             ###   ########.fr       */
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
	x = -1;
	while (str[0] == '<' && infile[++x])
	{
		fin = ft_split_shell(infile[x], ">");
		if ((str[0] == '<' && has_more_str(fin[0], " \t\n\v\f\r")) || \
(fin[1] && has_more_str_all(&fin[1], " \t\n\v\f\r")))
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
static int	count_infile(char **res)
{
	int		x;
	char	*tmp;
	int		count;

	count = 0;
	x = -1;
	while (res[++x])
	{
		tmp = skip_spaces(res[x], " \t\n\v\f\r");
		if (ft_strchr(tmp, '<'))
			count += start_count_infile(tmp);
	}
	return (count);
}

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
	char	*cmd_tail;

	x = -1;
	i = 0;
	while (res[++x])
	{
		cmd_tail = skip_spaces(res[x], " \t\n\v\f\r");
		tmp = ft_split_shell(cmd_tail, ">");
		if (tmp && tmp[1])
		{
			i += count_str_array(&tmp[1]);
			if (cmd_tail[0] == '>' && has_more_str_all(tmp, set))
				i++;
		}
		else if (!tmp[1] && cmd_tail[0] == '>' && has_more_str_all(tmp, set))
			i++;
		free_chr_ptr((void **)tmp);
	}
	return (i);
}

/*
 * *i counts number of string combos for malloc later
 * checks if < << is at beginning, process entire line til pipe
 * if infile at middle, all strings after < are filenames
 */
int	get_malloc_size(char **res)
{
	int		i;

	i = 0;
	i = count_str_array(res);
	i += count_str_array(&res[1]);
	i += count_infile(res);
	i += count_cmd_tail(res, " \t\n\v\f\r");
	return (i);
}
