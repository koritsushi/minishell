/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:12:43 by hsim              #+#    #+#             */
/*   Updated: 2025/05/30 16:16:10 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

/*
 * child function in extract_vars
 * returns a pointer to the beginning of next variable
 * if encounter ' " after equal_sign, skip & return
 * if encounter ' ", without equal_sign, skip only
 * if encounter spaces, break
 */
static char	*find_next_var(char *str)
{
	int	f_equal_sign;

	f_equal_sign = 0;
	while (str && str[0])
	{
		if (str[0] == '=')
			f_equal_sign = 1;
		if (str[0] == '\'' || str[0] == '\"')
		{
			str = skip_if_quote(str, str[0], 0);
			if (str[1] && is_target(" \t\n\v\f\r", str[1]))
				return (skip_spaces(str + 1, " \t\n\v\f\r"));
			if (f_equal_sign && (str[0] == '\'' || str[0] == '\"'))
				return (str + 1);
			if (f_equal_sign)
				return (str);
		}
		else if (str[0] && is_target(" \t\n\v\f\r", str[0]))
			return (skip_spaces(str, " \t\n\v\f\r"));
		str++;
	}
	return (NULL);
}

/*
 * child function in get_variable
 * trims all cmd_line to skip or free valid var assignment (var=123)
 * so that it dont get passed to execution
 */
void	remove_var(t_token *lst)
{
	int	i;
	int	valid_fd;

	i = -1;
	valid_fd = check_infile_fd(*lst);
	while (lst->data[++i])
	{
		while (lst->data[i] && lst->datatype[i] != WORD)
			i++;
		if (!lst->data[i] || !lst->data[i][0])
			break ;
	if (((valid_export_keyword(lst->data[i], 0)) && !valid_fd) || \
check_var_syntax(&lst->data[i]))
		{
			free(lst->data[i]);
			lst->data[i] = ft_strdup("");
		}
	}
}

/*
 * child function in extract_vars,
 * adds new var entry to the end of linked list
 * updates export_id to respective values~
 * export_id: 0 (var=text) none
 * export_id: 1 (export var) export only
 * export_id: 2 (export var=, export var=1) export && env
 * uses malloc
 */
static void	add_var_entry(t_env **vars, char *name, char *new, int export_id)
{
	t_env	*lst;

	lst = ft_lstnew_sh(name, new, export_id);
	ft_lstadd_back_sh(vars, lst);
}

/*
 * child function in process_vars,
 * searches & replace duplicate var name in linked list, 
 * or add new var entry to list
 * types of export_id values~
 * export_id: 0 (var=text) none
 * export_id: 1 (export var) export only
 * export_id: 2 (export var=, export var=1) export && env
 */
void	extract_vars(t_env **vars, char *str, int export_id)
{
	char	*name;
	char	*new;

	while (str && str[0])
	{
		str = skip_spaces(str, " \t\n\v\f\r");
		if (!get_var_name(&name, str))
			return ;
		if (is_valid_var_name(&name, export_id))
		{
			new = NULL;
			if (!malloc_chr_ptr(&new, count_malloc_vars(str) + 1))
				return ;
			copy_vars(new, str, count_malloc_vars(str));
			if (!check_replace_dup(*vars, name, new, export_id))
				add_var_entry(vars, name, new, export_id);
			free(new);
		}
		free(name);
		str = find_next_var(str);
	}
}
