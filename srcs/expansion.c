/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:29:17 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/10 18:56:28 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

// 24 lines!
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
	/* cmd_line is the entire pipeline */
	/* if str[0] == {, 
	 * check if has } and ',' in between
	 * if encounter spaces ' ', dont expand
	 */
	x = 0;
	flag_quote = 0;
	if (!is_target(*cmd_line, '{'))
		return ;
	while (str && str[0])
	{
		// /*debug*/printf("\033[93mbrace_expansion:ent:\033[0m%s.\n", str);
		if (str[0] && (is_target(" \t\n\v\f\r", str[0]) && !flag_quote))
			x = -1;
		update_flag_quote(str, &symbol, &flag_quote);
		// /*debug*/printf("str:%s, flag_q:%d\n", str, flag_quote);

		if (str[0] == '$' && str[1] == '{')
			str += 2;
		/* have to be beginning of str: r"{,} , then enter immediately*/
		// else if (has_valid_brace_content(str) && flag < 1)
		else if (str[0] == '{' && str[1] != '{' && !flag_quote && \
		has_valid_brace_content(str))
			str = perform_brace_expansion(str, cmd_line, &x);
		else
			str++;
		x++;
	}
}

// 24 lines!
/*
 * checks if there are $var in string and corresponding entry in t_env vars
 * yes: replace, free, remalloc cmd_line with content
 * no : replace with spaces ' '
 * uses malloc
 */
void	shell_var_expansion(char **cmd_line, t_env *vars, int exit_status)
{
	char	*str;
	int		flag;
	// int		x;

	str = *cmd_line;
	flag = 0;
	while (str && str[0])
	{
		// /*debug*/printf("shell_var_expansion:ent:%s\n", str);
		if (str[0] == '\"')
			flag = 1;
		if (!flag && str[0] == '\'' && ft_strchr(str + 1, '\''))
			str = ft_strchr(str + 1, '\'') + 1;
		else if (str[0] == '$' && ft_isalpha(str[1]))
		{
			/*debug*/printf("shell_var_expansion:flag:%d\n", flag);
			str = expand_shell_var(vars, cmd_line, str);
			if (flag)
				flag = 0;
		}
		else if (str[0] == '$' && str[1] && str[1] == '?')
		{
			str = expand_exit_status(cmd_line, exit_status);
			/*debug*/printf("shell_var_expansion:exit:%s %d\n", str, exit_status);
		}
		else if (str[0] == '$' && str[1] && str[1] == '$')
			str += 2;
		else
			str++;
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
	/*debug*/printf("quote_removal:len:%d\n", len);
	if (!malloc_chr_ptr(&new, len + 1))
		return ;
	expand_quote_removal(*cmd_line, new);
	free(*cmd_line);
	*cmd_line = new;
}

int	cmd_expansion(char **lst_data, t_env *vars, int exit_status)
{
	int		x;

	x = -1;
	while (lst_data && lst_data[++x])
	{
		/*debug*/printf("cmd_expansion:ent:%s\n", lst_data[x]);
		brace_expansion(&lst_data[x]);
		/*debug*/printf("cmd_expansion:brace:%s\n", lst_data[x]);
		shell_var_expansion(&lst_data[x], vars, exit_status);
		/*debug*/printf("cmd_expansion:sh_var:%s\n", lst_data[x]);
		quote_removal(&lst_data[x]);
	}
	return (1);
}
