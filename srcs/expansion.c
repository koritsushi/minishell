/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:29:17 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/02 14:45:13 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

// 27 lines!
/*
 * checks if there are braces expansion {,} in cmd_line
 * search until found the head of {,}
 * yes/found: expand and replace the cmd_line by freeing & re-malloc
 */
void	brace_expansion(char **cmd_line)
{
	char	*str;
	int		x;
	int		len;
	int		flag_quote;
	char	symbol;
	(void)	len;

	str = *cmd_line;
	/* cmd_line is the entire pipeline */
	/* if str[0] == {, 
	 * check if has } and ',' in between
	 * if encounter spaces ' ', dont expand
	 */
	x = 0;
	flag_quote = 0;
	symbol = '\0';
	// int flag = 0;
	if (!is_target(str, '{'))
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
		else if (str[0] == '{' && str[1] != '{' && has_valid_brace_content(str) && !flag_quote)
		{
			len = ft_strlen(*cmd_line) - 2 + get_expansion_count(str - x);
			/*debug*/printf("\033[93mbrace_expansion:\033[0mstr:%s. x:%d\n", str - x, x);
			/*debug*/printf("\033[93mvalid brace!! %d+1\033[0m\n", len);
			/* propose to put str in perform_brace_expansion */
			perform_brace_expansion(cmd_line, str - x, len);
			str = *cmd_line;
			x = -1;
			// flag += 1;
			// str++;
		}
		else
			str++;
		x++;
	}
}

// need to split
/*
 * checks if there are $var in string and corresponding entry in t_env vars
 * yes: replace with content
 * no : replace with spaces ' '
 */
void	shell_var_expansion(char **cmd_line, t_env *vars, int exit_status)
{
	char	**tmp;
	char	**fin;
	char	*str;
	int		flag;

	str = *cmd_line;
	flag = 0;
	while (str && str[0])
	{
		// /*debug*/printf("shell_var_expansion:ent:%s\n", str);
		if (str[0] == '\"')
			flag = 1;
		if (str[0] == '\'' && !flag)
			str = ft_strchr(str + 1, '\'') + 1;
		else if (str[0] == '$' && ft_isalpha(str[1]))
		{
			tmp = ft_split_shell(str, "$");
			// /*debug*/printf("-----\nsplit:fin:\n");
			fin = ft_split_shell(tmp[0], " \'\"\t\n\v\f\r");
			// /*debug*/printf("-----\nshell_var_expansion:tmp:\n");
			// /*debug*/debug_print(tmp);
			// /*debug*/printf(".....\nfin:\n");
			// /*debug*/debug_print(fin);
			// /*debug*/printf("-----\n");
			/*debug*/printf("var_name:%s, str:%s\n", fin[0], str);
			check_shell_var(vars, fin[0], cmd_line, str);
			free_multiple_ptr(2, tmp, fin);
			str = *cmd_line;
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

int	cmd_expansion(char **lst_data, t_env *vars, int exit_status)
{
	(void)	vars;
	(void)	exit_status;
	int		x;

	x = -1;
	while (lst_data && lst_data[++x])
	{
		/*debug*/printf("cmd_expansion:ent:%s\n", lst_data[x]);
		// shell_var_expansion(&lst_data[x], vars, exit_status);
		brace_expansion(&lst_data[x]);
		/* " '	quote_removal	*/
	}
	return (1);
}
