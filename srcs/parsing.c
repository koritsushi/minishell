/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:54:11 by hsim              #+#    #+#             */
/*   Updated: 2025/06/02 15:11:35 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * parsing section here saves variable assignments to linked list,
 * checks syntax error & replace processed vars with spaces ' '
 ---------------------------------------------------------------------------- */

#include "includes/parsing.h"

/*
 * child function in start_get_variable
 * skips keyword 'export' & update dependant values
 */
static char	*skip_export_update_val(char *new, int *export_id)
{
	*export_id = 2;
	return (skip_to_next_space(new));
}

/*
 * child function in start_get_variable
 * checks if infile_fd valid, if invalid, return 0
 */
int	check_infile_fd(t_token lst)
{
	int	i;
	int	flag;
	int	fd;

	i = -1;
	flag = 1;
	while (lst.data[++i] && flag)
	{
		if (lst.datatype[i] == INFILE)
		{
			fd = open(lst.data[i], O_RDONLY);
			if (fd == -1)
				flag = 0;
			else
				close(fd);
		}
		else if (lst.datatype[i] == PIPE)
			break ;
	}
	return (flag);
}

/*
 * child function in get_variable
 * skips 1st export keyword, checks if infile_fd is valid
 * extract_vars/env & save to t_env
 */
int	start_get_variable(t_env **vars, t_token lst, char *new)
{
	int	export_id;
	int	valid_fd;

	valid_fd = 1;
	export_id = 0;
	if (valid_export_keyword(new, 0))
	{
		new = skip_export_update_val(new, &export_id);
		if (!check_infile_fd(lst))
			valid_fd = 0;
	}
	if (!new && valid_fd)
		return (0);
	else if (valid_fd)
		extract_vars(vars, new, export_id);
	return (1);
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

	i = 0;
	while (lst.data[i] && lst.datatype[i] != WORD)
		i++;
	if (!lst.data[i] || !lst.data[i][0])
		return (0);
	if (check_var_syntax(&lst.data[i]))
	{
		new = lst.data[i];
		if (!is_target(str, '|'))
			if (!start_get_variable(vars, lst, new))
				return (0);
	}
	remove_var(&lst);
	return (1);
}
