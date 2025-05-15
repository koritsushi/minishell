/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:28:58 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/15 12:34:02 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

/* syntax checking for main cmd lines */

/*
 * child function in if_double_symbol
 * checks if syntax error condition is matched
 */
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
		// /*debug*/printf("*******tmp:%s.\n", tmp);
		if (tmp[1] && tmp[1] == symbol)
		{
			tmp += steps;
			// /*debug*/printf("tmp+= %s\n", tmp);
		}
		if ((tmp[0] && tmp[1] && !is_target("<>|=&", tmp[1])) || \
			(tmp[0] == '=' && tmp[1] == '\0'))
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
			return (ft_perror_fd("' detected!\n", 2, 1));
		}
		else if (!res[1] && !tmp[1])
			return (\
ft_perror_fd("🚨 Syntax error! field empty after operator\n", 2, 1));
		tmp++;
	}
	return (0);
}

/*
 * child function in check_syntax
 * check if there are invalid or unclosed symbols
 */
int	check_symbols(char **res)
{
	int		x;

	x = -1;
	if (res[0][0] == '|' || res[0][0] == '=')
		return \
(ft_perror_fd("🚨 Syntax error! unexpected symbol detected!\n", 2, 0));
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
		if (res[x][0] && res[x][1] && is_target("$", res[x][0]) && \
			res[x][1] == '{' && !ft_strchr(&res[x][1], '}'))
			return \
(ft_perror_fd("🚨 Syntax error! Brace unclosed after '$'\n", 2, 0));
	}
	return (1);
}

int	check_unclosed_quote(char *str)
{
	char	*new;

	new = str;
	while (new[0])
	{
		// /*debug*/printf("check_unclosed_quote:ent:%s\n", new);
		if (new[0] && is_target("\'\"", new[0]))
		{
			new = skip_if_quote(new, new[0], 0);
			if (new)
				/*debug*/printf("check_unclosed_quote:%s.\n", new);
		}
		if (!new)
			return \
(ft_perror_fd("🚨 Syntax error! unclosed quote detected!\n", 2, 0));
		new++;
	}
	return (1);
}

int	check_syntax(char *str)
{
	char	**res;
	int		flag;

	flag = 1;
	str = skip_spaces(str, " \t\n\v\f\r");
	if (!str[0])
		return (0);
	res = ft_split_shell(str, " \t\n\v\f\r");
	/*debug*/printf("check_syntax\n--------\nres:\n");
	/*debug*/debug_print(res);
	/*debug*/printf("--------\n");

	if (res && (!check_symbols(res) || !check_unclosed_quote(str)))
		flag = 0;
	free_chr_ptr((void **)res);
	return (flag);
}
