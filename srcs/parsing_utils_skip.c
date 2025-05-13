/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_skip.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:05:39 by hsim              #+#    #+#             */
/*   Updated: 2025/05/13 07:25:02 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

/*
 * if str[0] == symbol, will skip to the next occurence of symbol
 * if flag == 1, will skip all spaces followed after result
 * returns skipped result
 */
char	*skip_if_quote(char *str, char symbol, int flag)
{
	char	*new;

	new = str;
	if (str[0] == symbol)
	{
		/*debug*/printf("skip \033[35m%c\033[0m =\033[90m%s\033[0m\n", symbol, new);
		// /*debug*/printf("new: \033[35m%c\033[0m\033[90m%s\033[0m\n", new[0], new + 1);
		// /*debug*/printf("\033[90msym:%c %d skip_quote:strchr: %s\033[0m\n", symbol, (int)symbol, new + 1);
		new = ft_strchr(new + 1, (int)symbol);
		/*debug*/printf("after_skip_quote=\033[90m%s\033[0m.\n", new);
		if (flag && new && new[1] && is_target(" \t\n\v\f\r", new[1]))
			return (skip_spaces(new + 1, " \t\n\v\f\r"));
	}
	return (new);
}

/*
 * child function in process_vars,
 * skips all < infile & > outfile redirections that are at the beginning of str,
 * returns result to char*
 */
char	*skip_redirs(char *str)//, char **new)
{
	char	*new;

	new = str;
	while (str[0] == '<' || str[0] == '>')
	{
		new = skip_spaces(new, "<> \t\n\v\f\r");
		/*debug*/printf("skip_spaces=%s\n", new);
		new = skip_if_symbol(new, str[0], '<');
		/*debug*/printf("skip_< =%s\n", new);
		new = skip_if_symbol(new, str[0], '>');
		/*debug*/printf("skip_> =%s\n", new);
		str = skip_spaces(str, "<> \t\n\v\f\r");
		while (str[0] && !is_target(" \t\n\v\f\r", str[0]))
			str++;
		str = skip_spaces(str, " \t\n\v\f\r");
		/*debug*/printf("str =%s\n", str);
		new = str;
	}
	return (new);
}
