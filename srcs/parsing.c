/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:54:11 by hsim              #+#    #+#             */
/*   Updated: 2025/05/29 18:26:15 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * parsing section here saves variable assignments to linked list,
 * checks syntax error & replace processed vars with spaces ' '
 ---------------------------------------------------------------------------- */

#include "includes/parsing.h"

/*
 * child function in valid_export_keyword
 * checks if str == keyword up to len
 * flag = 0: no spaces after keyword
 * flag = 1: has spaces after keyword
 */
static int	check_export_keyword(char *str, char *keyword, int len, int flag)
{
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
	if (\
check_export_keyword(str, "export", 6, flag) || \
check_export_keyword(str, "\'export\'", 8, flag) || \
check_export_keyword(str, "\"export\"", 8, flag))
		return (1);
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

/*
 * checks if variable syntax is correct,
 * overwrite & save if variable exists
 * removes entire var line after finish get_variable
 * types of export_id values~
 * export_id: 0 (var=text) none
 * export_id: 1 (export var) export only
 * export_id: 2 (export var=, export var=1) export && env
 */
int	get_variable(t_env **vars, t_token lst, char *str)
{
	char	*new;
	int		i;
	int		export_id;

	export_id = 0;
	i = 0;
	while (lst.data[i] && lst.datatype[i] != WORD)
		i++;
	if (!lst.data[i] || !lst.data[i][0])
		return (0);
	if (check_var_syntax(&lst.data[i]))
	{
		new = lst.data[i];
		if (!is_target(str, '|'))
		{
			if (valid_export_keyword(new, 0))
				new = skip_export_update_val(new, &export_id);
			if (!new)
				return (0);
			extract_vars(vars, new, export_id);
		}
	}
	remove_var(&lst);
	return (1);
}
