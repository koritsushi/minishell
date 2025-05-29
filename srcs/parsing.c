/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:54:11 by hsim              #+#    #+#             */
/*   Updated: 2025/05/29 16:04:46 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * parsing section here saves variable assignments to linked list,
 * checks syntax error & replace processed vars with spaces ' '
 ---------------------------------------------------------------------------- */

#include "includes/parsing.h"

// 19 lines!
/*
 * child function in get_variable, saves variables in linked list
 * types of export_id values~
 * export_id: 0 (var=text) none
 * export_id: 1 (export var) export only
 * export_id: 2 (export var=, export var=1) export && env
 */
// void	process_vars(t_env **vars, char *str, int export_id)
// {
// 	char	*new;
// 	char	**tmp;
// 	char	**fin;
// 	int		x;

// 	/*split infile & outfile*/
// 	/* <infile var=123 > outfile */
// 	/* <infile > outfile var=123*/

// 	/* <infile var=123 */
// 	/* var=123 < infile */
// 	/* > outfile var=123 */
// 	/* var=123 > outfile*/
// 	/* var=123 var2=456 > outfile >out2 */

// 	/* if var var, save last var	*/
// 	/* if var1 var2, save both var	*/
// 	/* save var: skip ' " quotes	*/
// 	if (!str)
// 		return ;
// 	new = str;
// 	/*debug*/printf("process_vars:ent:%s.\n", new);
// 	/* if at beginning < > */
// 	// <in1 in2 <in3 var=888 >out
// 	if (has_more_str(new, "<>"))
// 	{
// 		x = 0;
// 		tmp = ft_split_shell(new, "<>");
// 		fin = ft_split_shell(tmp[0], " \t\n\v\f\r");

// 		/*debug*/printf("--------\ntmp:\n");
// 		/*debug*/debug_print(tmp);
// 		/*debug*/printf("--------\nfin:\n");
// 		/*debug*/debug_print(fin);

// 		while (fin && fin[x])
// 			extract_vars(vars, fin[x++], export_id);

// 		// /*debug*/printf("tmp[0]:%s.\n", tmp[0]);
// 		free_multiple_ptr(tmp, fin, NULL);
// 	}
// 	else
// 		extract_vars(vars, new, export_id);
// }

/*
 * child function in valid_export_keyword
 * checks if str == keyword up to len
 * flag = 0: no spaces after keyword
 * flag = 1: has spaces after keyword
 */
static int	check_export_keyword(char *str, char *keyword, int len, int flag)
{
	if (!str || !keyword)
		return (0);
	if (ft_strncmp(str, keyword, len) == 0)
	{
		if ((flag && str[len] && is_target(" \t\n\v\f\r", str[len])) || !flag)
			return (1);
	}
	return (0);
}

/*
 * child function in get_variable & is_valid_var_name
 * checks if string starts with export 'export' or "export"
 * return 1 if valid
 * flag 0 = only checks if it is keyword export
 * flag 1 = checks keyword + if has spaces ' ' after keyword
 */
int	valid_export_keyword(char *str, int flag)
{
	if (!str)
		return (0);
	str = skip_spaces(str, " \t\n\v\f\r");
	// /*debug*/printf("valid_export_keyword:ent:%s.\n", str);

	if (\
check_export_keyword(str, "export", 6, flag) || \
check_export_keyword(str, "\'export\'", 8, flag) || \
check_export_keyword(str, "\"export\"", 8, flag))
		return (1);
	// /*debug*/printf("valid_export_keyword:invalid! %c\n", str[6]);
	return (0);
}

/*
 * child function in get_variable
 * skips keyword 'export' & update dependant values
 */
static char	*skip_export_update_val(char *new, int *export_id)
{
	*export_id = 2;
	return (skip_if_symbol(new, 'c', 'c'));
}

// 24 lines!
/*
 * checks if variable syntax is correct,
 * overwrite & save if variable exists
 * removes entire var line after finish get_variable
 * types of export_id values~
 * export_id: 0 (var=text) none
 * export_id: 1 (export var) export only
 * export_id: 2 (export var=, export var=1) export && env
 */
int	get_variable(t_env **vars, t_token lst, char *str, int exit_status)
{
	char	*new;
	int		i;
	int		export_id;
	(void)	str;
	(void)	vars;
	(void)	exit_status;

	export_id = 0;
	// skip all redirs
	// check valid export keyword
	// check syntax
	// if no pipes, do the rest
	i = 0;
	while (lst.data[i] && lst.datatype[i] != WORD)
		i++;
	if (!lst.data[i] || !lst.data[i][0])
		return (0);
	// /*debug*/printf("get_variable:ent:%s.\n", lst.data[i]);
	if (check_var_syntax(&lst.data[i]))
	{
		// /* if no pipes, copy_vars */
		// // /*debug*/printf("check_var_syntax:enter! new:%s, str:%s\n", new, str);
		new = lst.data[i];
		if (!is_target(str, '|'))
		{
			if (valid_export_keyword(new, 0))
			{
				new = skip_export_update_val(new, &export_id);
				// /*debug*/printf("valid export! %s\n", new);
			}
			if (!new)
				return (0);
			// /*debug*/printf("get_var:%s.\n", new);
			extract_vars(vars, new, export_id);
		}
	}
	remove_var(&lst);
	// /*debug*/printf("updated_str:%s.\n", str);
	return (1);
}
