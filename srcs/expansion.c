/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:29:17 by mliyuan           #+#    #+#             */
/*   Updated: 2025/03/18 14:00:34 by hsim             ###   ########.fr       */
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
		shell_var_expansion(&lst_data[x], vars);
		/* {}	brace_expansion	*/
		/* ~	tilde_expansion	*/
		/* " '	quote_removal	*/
	}
	return (1);
}
