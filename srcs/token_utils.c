/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:18:26 by hsim              #+#    #+#             */
/*   Updated: 2025/05/24 16:34:05 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/* skips if str[0] == *set, stops when str[0] != *set */
char	*skip_spaces(char *str, char *set)
{
	char	*tmp;

	tmp = str;
	while (tmp && tmp[0] && is_target(set, tmp[0]))
		tmp++;
	return (tmp);
}

/* 
 * child function for extract_cmd_head & process_cmd_tail
 * *str = the string to check/iterate
 * if char c == symbol, skips *str to the 1st occurence of spaces
 * and skips all consequent spaces
 */
char	*skip_if_symbol(char *str, char c, char symbol)
{
	if (c == symbol)
	{
		str = ft_strchr(str, ' ');
		str = skip_spaces(str, " \t\n\v\f\r");
	}
	return (str);
}

/* splits current *str by *set and see if there are strings after splitting */
int	has_more_str(char *str, char *set)
{
	char	**check;
	int		res;

	res = 0;
	check = ft_split_shell(str, set);
	if (check && check[1])
		res = 1;
	if (check)
		free_chr_ptr((void **)check);
	return (res);
}

/*
 * checks all pointer array **str by *set 
 * and see if there are strings after splitting
 */
int	has_more_str_all(char **str, char *set)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (has_more_str(str[i], set))
			return (1);
		i++;
	}
	return (0);
}
