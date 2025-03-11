/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:28:58 by mliyuan           #+#    #+#             */
/*   Updated: 2025/03/11 14:34:43 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

static int	match_condition(char **res, char *tmp, char symbol)
{
	if (!tmp)
		return (0);
	if (tmp[1] == symbol)
		return (1);
	else if (tmp[1] && tmp[1] == '=')
		return (1);
	else if (res[1] && (res[1][0] == symbol || res[1][0] == '='))
		return (1);
	else if (symbol != '|')
	{
		// /*debug*/printf("hi= %s\n", tmp);
		if (tmp[1] && is_target("<>|", tmp[1]))
			return (1);
		else if (res[1] && is_target("<>|", res[1][0]))
			return (1);
	}
	return (0);
}

// 25 lines!
/*
 * checks res[0] string if has double char symbols
 * int steps = steps to skip after found symbol (for symbol repeats > 2)
 * by default steps = 0
 */
int	if_double_symbol(char **res, char symbol, int steps)
{
	char	*tmp;

	tmp = res[0];
	while (tmp && tmp[0] && is_target(tmp, symbol))
	{
		tmp = ft_strchr(tmp, symbol);
		// /*debug*/printf("*******tmp=%s\n", tmp);
		if (tmp[1] && tmp[1] == symbol)
		{
			tmp += steps;
			// /*debug*/printf("tmp+= %s\n", tmp);
		}
		if (tmp[0] && tmp[1] && !is_target("<>|=& \t\n\v\f\r", tmp[1]))
		{
			// /*debug*/printf("tmp[0]=%c, tmp[1]=%c, break!\n", tmp[0], tmp[1]);
			break ;
		}
		if (match_condition(res, tmp, symbol))
		{
			ft_putstr_fd("🚨 Syntax error! field empty after '", 2);
			write(2, &symbol, 1);
			ft_putstr_fd("' or more than 2 '", 2);
			write(2, &symbol, 1);
			ft_putstr_fd("' detected!\n", 2);
			return (1);
		}
		else if (!res[1] && !tmp[1])
			return (\
			ft_perror_fd("🚨 Syntax error! field empty after operator\n", 2, 1));
		tmp++;
	}
	return (0);
}

int	check_symbols(char **res)
{
	int		x;

	x = -1;
	if (res[0][0] == '|')
		return \
		(ft_perror_fd("🚨 Syntax error! unexpected '|' detected!\n", 2, 0));
	while (res[++x])
	{
		if (is_target(res[x], '&'))
			return (ft_perror_fd("🚨 Syntax error! '&' detected!\n", 2, 0));
		if (is_target(res[x], ';'))
			return (ft_perror_fd("🚨 Syntax error! ';' detected!\n", 2, 0));
		if (if_double_symbol(&res[x], '|', 0) || \
			if_double_symbol(&res[x], '=', 0) || \
			if_double_symbol(&res[x], '<', 1) || \
			if_double_symbol(&res[x], '>', 1))
			return (0);
	}
	return (1);
}

int	check_unclosed_quote(char *str)
{
	int		flag;
	char	*new;

	new = str;
	flag = 0;
	while (new && new[0])
	{
		// /*debug*/printf("enter=%s\n", new);
		if (new[0] == '\'' || new[0] == '"')
			new = skip_if_quote(new, new[0]);
		if (!new)
		{
			return (ft_perror_fd("🚨 Syntax error! unclosed quote detected!\n", 2, 0));
			return (0);
		}
		new++;
	}
	return (1);
}

/* scans through *str and see if any in *set is detected */
// int	has_target(char *str, char *set)
// {
// 	while (str[0])
// 	{
// 		if (is_target(set, str[0]))
// 			return (1);
// 		str++;
// 	}
// 	return (0);
// }

int	check_syntax(char *str)
{
	char	**res;
	int		flag;

	flag = 1;
	res = ft_split_shell(str, " \t\n\v\f\r");
	// /*debug*/printf("--------\nres:\n");
	// /*debug*/debug_print(res);
	// /*debug*/printf("--------\n");

	if (!check_symbols(res))
		flag = 0;
	if (!check_unclosed_quote(str))
		flag = 0;
	free_chr_ptr((void **)res);
	return (flag);
}
