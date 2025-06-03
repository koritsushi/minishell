/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:28:58 by mliyuan           #+#    #+#             */
/*   Updated: 2025/06/03 12:37:14 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* syntax checking for main cmd lines */

#include "includes/parsing.h"

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
		if (new[0] && is_target("\'\"", new[0]))
			new = skip_if_quote(new, new[0], 0);
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
	if (!str || !str[0])
		return (0);
	res = ft_split_shell(str, " \t\n\v\f\r");
	if (res && (!check_symbols(res) || !check_unclosed_quote(str)))
		flag = 0;
	free_chr_ptr((void **)res);
	return (flag);
}
