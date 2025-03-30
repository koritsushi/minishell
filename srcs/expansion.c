/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:29:17 by mliyuan           #+#    #+#             */
/*   Updated: 2025/03/30 08:47:16 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

/*
	scan and tokenize all of these characters
	' ' ' single quote
	' " ' double quote
	' < ' redirect input
	' > ' redirect output
	" << " delimiter
	" >> " redirect output append mode
	' | ' pipe
	' $ ' environment variables 
*/

/*
 * checks if there are braces expansion {,} in cmd_line
 * yes: expand and replace the cmd_line by freeing & re-malloc
 */
void	brace_expansion(char **cmd_line)
{
	char	*str;
	int		x;
	int		flag; //remove
	int		len;

	str = *cmd_line;
	flag = 0; //remove
	/* cmd_line is the entire pipeline */
	/* if str[0] == {, 
	 * check if has } and ',' in between
	 * if encounter spaces ' ', dont expand
	 */
	x = 0;
	while (str && str[0] && !flag)
	{
		// /*debug*/printf("\033[93mbrace_expansion:ent:\033[0m%s.\n", str);
		if (str[0] && is_target(" \t\n\v\f\r", str[0]))
			x = -1;
		if (str[0] == '\'')
			str = ft_strchr(str + 1, '\'') + 1;
		else if (str[0] == '$' && str[1] == '{')
			str += 2;
		else if (str[0] == '{' && str[1] != '{' && has_valid_brace_content(str))
		{
			len = ft_strlen(*cmd_line) - 2;
			/*debug*/printf("\033[93mbrace_expansion:\033[0mstr:%s. x:%d\n", str, x);
			len += get_expansion_count(str - x);
			/*debug*/printf("\033[93mvalid brace!! %d+1\033[0m\n", len);
			perform_brace_expansion(cmd_line, len);
			// flag = 1; //temporary
			str = *cmd_line;
			x = -1;
		}
		else
			str++;
		x++;
	}
}

/*
 * checks if there are $var in string and corresponding entry in t_list vars
 * yes: replace with content
 * no : replace with spaces ' '
 */
void	shell_var_expansion(char **cmd_line, t_list *vars)
{
	char	**tmp;
	char	**fin;
	char	*str;

	str = *cmd_line;
	while (str && str[0])
	{
		// /*debug*/printf("shell_var_expansion:ent:%s\n", str);
		if (str[0] == '\'')
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
		else if (str[0] == '$' && str[1] == '$')
			str += 2;
		else
			str++;
	}
}

int	cmd_expansion(char **lst_data, t_list *vars)
{
	int		x;

	x = -1;
	while (lst_data && lst_data[++x])
	{
		/*debug*/printf("cmd_expansion:ent:%s\n", lst_data[x]);
		shell_var_expansion(&lst_data[x], vars);
		brace_expansion(&lst_data[x]);
		/* {}	brace_expansion	*/
		/* ${}	shell_var_brace_expansion	*/
		/* ~	tilde_expansion	*/
		/* " '	quote_removal	*/
	}
	return (1);
}
