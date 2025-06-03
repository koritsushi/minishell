/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_check2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:35:54 by hsim              #+#    #+#             */
/*   Updated: 2025/06/03 12:39:01 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

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

char	*ft_strchr_sh(char *str, char c)
{
	int		flag_quote;
	char	symbol;

	flag_quote = 0;
	symbol = '\0';
	if (!str)
		return (str);
	while (str && str[0])
	{
		update_flag_quote(str, "\'\"", &symbol, &flag_quote);
		if (!flag_quote && str[0] == c)
			return (str);
		str++;
	}
	if (c == '\0')
		return (str);
	return (NULL);
}

/* helper if_double_symbol to shorten function*/
static int	err_message(char symbol)
{
	ft_putstr_fd("🚨 Syntax error! field empty after '", 2);
	write(2, &symbol, 1);
	ft_putstr_fd("' or more than 2 '", 2);
	write(2, &symbol, 1);
	return (ft_perror_fd("' detected!\n", 2, 1));
}

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
		tmp = ft_strchr_sh(tmp, symbol);
		if (!tmp)
			break ;
		if (tmp[1] && tmp[1] == symbol)
			tmp += steps;
		if ((tmp[0] && tmp[1] && !is_target("<>|=&", tmp[1])) || \
(tmp[0] == '=' && tmp[1] == '\0'))
			break ;
		if (match_condition(res, tmp, symbol))
			return (err_message(symbol));
		else if (!res[1] && !tmp[1])
			return (\
ft_perror_fd("🚨 Syntax error! field empty after operator\n", 2, 1));
		tmp++;
	}
	return (0);
}
