/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_extract2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:01:53 by hsim              #+#    #+#             */
/*   Updated: 2025/05/27 18:03:24 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/*
 * child function in copy_cmd_tail
 * overwrites any < infiles to ' ' spaces
 */
static void	overwrite_infile(char **cmd_tail)
{
	char	*str;
	char	symbol;
	int		flag;

	str = *cmd_tail;
	symbol = '\0';
	flag = 0;
	while (str[0])
	{
		update_flag_quote(str, "\'\"", &symbol, &flag);
		if (!flag && str[0] == '<')
		{
			while (is_target("< \t\n\v\f\r", str[0]))
				*str++ = ' ';
			while (!is_target(" \t\n\v\f\r", str[0]))
				*str++ = ' ';
		}
		else
			str++;
	}
}

// 15 lines!
/*
 * child function in extract_cmd_tail
 * scans through line and copies the correct cmds
 */
void	copy_cmd_tail(char **lst_data, int *start, char **outfile)
{
	char	*cmd_tail;
	int		i;

	i = -1;
	if (!outfile)
		return ;
	while (outfile[++i])
	{
		/* travel to the first space detected */
		cmd_tail = skip_spaces(outfile[i], " \t\n\v\f\r");
		cmd_tail = skip_if_symbol(cmd_tail, 'c', 'c');
		cmd_tail = skip_consecutive_redir(cmd_tail, 0);

		if (is_target(cmd_tail, '<'))
			overwrite_infile(&cmd_tail);

		// /*debug*/printf("***cmd_tail=%s| %zu\n", cmd_tail, ft_strlen(cmd_tail));
		// /*debug*/printf("copy_cmd_tail:%s.\n", cmd_tail);
		if (cmd_tail && cmd_tail[0])
		{
			cmd_tail -= 1;
			ft_strlcpy(&(*lst_data)[(*start)], cmd_tail, ft_strlen(cmd_tail) + 1);
			(*start) += ft_strlen(cmd_tail);
		}
	}
}
