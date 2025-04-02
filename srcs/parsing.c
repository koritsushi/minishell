/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:54:11 by hsim              #+#    #+#             */
/*   Updated: 2025/04/01 15:18:15 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

/*
 * parsing section here saves variable assignments to linked list,
 * checks syntax error & replace processed vars with spaces ' '
 ---------------------------------------------------------------------------- */

/*
 * if str[0] == symbol, will skip to the next occurence of symbol
 * if flag == 1, will skip all spaces followed after result
 * returns skipped result
 */
char	*skip_if_quote(char *str, char symbol, int flag)
{
	char	*new;

	new = str;
	if (str[0] == symbol) // ' "
	{
		/*debug*/printf("skip \033[35m%c\033[0m =\033[90m%s\033[0m\n", symbol, new);
		// /*debug*/printf("new: \033[35m%c\033[0m\033[90m%s\033[0m\n", new[0], new + 1);
		new = ft_strchr(new + 1, symbol);
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

// 19 lines!
/*
 * child function in get_variables, saves variables in linked list
 * types of export_id values~
 * export_id: 0 (var=text) none
 * export_id: 1 (export var) export only
 * export_id: 2 (export var=, export var=1) export && env
 */
void	process_vars(t_env **vars, char *str, int export_id)
{
	char	*new;
	char	**tmp;
	char	**fin;
	int		x;

	/*split infile & outfile*/
	/* <infile var=123 > outfile */
	/* <infile > outfile var=123*/

	/* <infile var=123 */
	/* var=123 < infile */
	/* > outfile var=123 */
	/* var=123 > outfile*/
	/* var=123 var2=456 > outfile >out2 */

	/* if var var, save last var	*/
	/* if var1 var2, save both var	*/
	/* save var: skip ' " quotes	*/
	if (!str)
	return ;
	new = str;
	/* if at beginning < > */
	if (has_more_str(new, "<>"))
	{
		x = 0;
		tmp = ft_split_shell(new, "<>");
		fin = ft_split_shell(tmp[0], " \t\n\v\f\r");

		/*debug*/printf("--------\ntmp:\n");
		/*debug*/debug_print(tmp);
		/*debug*/printf("--------\nfin:\n");
		/*debug*/debug_print(fin);
	
		while (fin && fin[x])
			extract_vars(vars, fin[x++], export_id);

		// /*debug*/printf("tmp[0]:%s.\n", tmp[0]);
		free_chr_ptr((void **)tmp);
		free_chr_ptr((void **)fin);
	}
	else
		extract_vars(vars, new, export_id);
}

// 18 lines!
/*
 * checks if variable syntax is correct,
 * overwrite & save if variable exists
 */
int	get_variable(t_env **vars, char *str)
{
	char	*new;
	int		flag;
	int		export_id;

	flag = 0;
	export_id = 0;
	new = skip_spaces(str, " \t\n\v\f\r");
	new = skip_redirs(new);

	/*debug*/printf("get_variable:ent:%s.\n", new);
	if (new[0] && !is_target(new, '=') && ft_strncmp(new, "export", 6) != 0)
		return (0);
	if (check_var_syntax(new, &flag))
	{
		/* if no pipes, copy_vars */
		// /*debug*/printf("check_var_syntax:enter! new:%s, str:%s\n", new, str);
		if (!is_target(new, '|') && !flag) //put a flag for multiple_cmd  // && !has_mix_redirs(new)
		{
			if (ft_strncmp(new, "export", 6) == 0)
			{
				new = skip_if_symbol(new, 'c', 'c');
				export_id = 2;
			}
			process_vars(vars, new, export_id);
		}
		// replace_var_space(new);
	}
	// /* check if its export */
	// new = skip_spaces(new, " \t\n\v\f\r");
	// if (ft_strncmp(new, "export", 6) == 0 && !is_target(new, '|'))
	// {
	// 	/*follow same process, just that == 1*/
	// 	new = skip_if_symbol(new, 'c', 'c');
	// 	/*debug*/printf("handle_Export!:%s\n", new);
	// 	process_vars(vars, new, 2);
	// 	// new = overwrite_export_line(new);
	// }
	/*debug*/printf("updated_str:%s.\n", str);
	return (1);
}
