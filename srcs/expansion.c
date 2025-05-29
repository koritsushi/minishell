/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:29:17 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/29 18:40:42 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

/*
 * checks if there are braces expansion {,} in cmd_line
 * search until found the head of {,}
 * yes/found: expand and replace the cmd_line by freeing & re-malloc
 */
void	brace_expansion(char **cmd_line)
{
	int		x;
	char	*str;
	char	symbol;
	int		flag_quote;

	str = *cmd_line;
	flag_quote = 0;
	symbol = '\0';
	x = 0;
	if (!is_target(*cmd_line, '{'))
		return ;
	while (str && str[0])
	{
		if (str[0] && (is_target(" \t\n\v\f\r", str[0]) && !flag_quote))
			x = -1;
		update_flag_quote(str, "\'\"", &symbol, &flag_quote);
		if (str[0] == '$' && str[1] == '{')
			str += 2;
		else if (str[0] == '{' && str[1] != '{' && !flag_quote && \
has_valid_brace_content(str))
			str = perform_brace_expansion(str, cmd_line, &x);
		else
			str++;
		x++;
	}
}

/*
 * child function in shell_var_expansion
 * skips quote & updates flag quote
 */
static void	skip_quote_update_flag(char *str, char *symbol, int *flag, int *x)
{
	*x += ft_strchr(&str[(*x) + 1], '\'') - &str[(*x)];
	update_flag_quote(&str[(*x)], "\'\"", symbol, flag);
	(*x)++;
}

/*
 * checks if there are $var in string and corresponding entry in t_env vars
 * yes: replace, free, remalloc cmd_line with content
 * no : replace with spaces ' '
 * b_switch=1 : expand_exit_status 
 * b_switch=0 : dont expand_exit_status 
 * uses malloc
 */
void	shell_var_expansion(char **cmd_line, t_env *vars, int exit_status)
{
	int		x;
	int		flag;
	char	*str;
	char	symbol;

	x = 0;
	flag = 0;
	symbol = '\0';
	str = *cmd_line;
	while (str && str[x])
	{
		update_flag_quote(&str[x], "\'\"", &symbol, &flag);
		if (flag && symbol == '\'' && str[x] == symbol)
			skip_quote_update_flag(str, &symbol, &flag, &x);
		else if (str[x] == '$' && (ft_isalpha(str[x + 1]) || str[x + 1] == '_'))
			str = expand_shell_var(vars, cmd_line, &str[x], &x);
		else if (str[x] == '$' && str[x + 1] && str[x + 1] == '?')
			str = expand_exit_status(cmd_line, exit_status, &x);
		else if (str[x] == '$' && str[x + 1] && str[x + 1] == '$')
			x += 2;
		else
			x++;
	}
}

/*
 * child function in cmd_expansion
 * removes quotes from string
 * count malloc, remallocs, copy over & return new updated string in cmd_line
 */
void	quote_removal(char **cmd_line)
{
	int		len;
	char	*new;

	if (!(*cmd_line) || \
(!is_target(*cmd_line, '\'') && !is_target(*cmd_line, '\"')))
		return ;
	len = count_malloc_quote_removal(*cmd_line);
	if (!malloc_chr_ptr(&new, len + 1))
		return ;
	expand_quote_removal(*cmd_line, new);
	free(*cmd_line);
	*cmd_line = new;
}

/* handles brace {,} & shell_var $var expansion */
int	cmd_expansion(char **lst_data, t_env *vars, int exit_status)
{
	int		x;

	x = -1;
	while (lst_data && lst_data[++x])
	{
		brace_expansion(&lst_data[x]);
		shell_var_expansion(&lst_data[x], vars, exit_status);
		dot_expansion(&lst_data[x]);
	}
	return (1);
}
