/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:05:39 by hsim              #+#    #+#             */
/*   Updated: 2025/05/29 18:01:24 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		new = ft_strchr(new + 1, (int)symbol);
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
char	*skip_redirs(char *str)
{
	char	*new;

	new = str;
	while (str[0] == '<' || str[0] == '>')
	{
		new = skip_spaces(new, "<> \t\n\v\f\r");
		new = skip_if_symbol(new, str[0], '<');
		new = skip_if_symbol(new, str[0], '>');
		str = skip_spaces(str, "<> \t\n\v\f\r");
		while (str[0] && !is_target(" \t\n\v\f\r", str[0]))
			str++;
		str = skip_spaces(str, " \t\n\v\f\r");
		new = str;
	}
	return (new);
}

/*
 * child function in skip_consecutive_infile
 * skips all spaces after c
 * breaks if found spaces when flag is off
 */
static char	*skip_consecutive(char *str, char c, char *stop)
{
	char	symbol;
	int		flag_quote;

	symbol = '\0';
	flag_quote = 0;
	while (str && str[0])
	{
		update_flag_quote(str, "\'\"", &symbol, &flag_quote);
		if (str[0] == c)
			str = skip_spaces(str, "<> \t\n\v\f\r");
		else if (is_target(stop, str[0]) && !flag_quote)
		{
			str = skip_spaces(str, " \t\n\v\f\r");
			if (str[0] != c)
				return (str);
		}
		else
			str++;
	}
	return (str);
}

/*
 * skips all consecutive infiles
 * if flag=1, skip >outfile
 */
char	*skip_consecutive_redir(char *outfile, int flag)
{
	char	*str;

	if (!outfile || !outfile[0])
		return (outfile);
	if (flag)
		str = skip_consecutive(outfile, '>', "< \t\n\v\f\r");
	else
		str = outfile;
	if (str[0] == '<')
		str = skip_consecutive(str, '<', "> \t\n\v\f\r");
	return (str);
}
