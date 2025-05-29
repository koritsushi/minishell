/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars_write.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:02:51 by hsim              #+#    #+#             */
/*   Updated: 2025/05/29 18:27:57 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* helper functions to malloc enough space for var
 * and save(copy) or overwrite existing entry
 * ************************************************************************** */

#include "includes/parsing.h"

/*
 * child function in extract_vars,
 * counts appropriate size to malloc string
 */
int	count_malloc_vars(char *str)
{
	int		i;
	char	symbol;
	int		flag;

	i = 0;
	flag = 0;
	symbol = '\0';
	while (str && str[0])
	{
		update_flag_quote(str, "\'\"", &symbol, &flag);
		if (!flag && is_target(" \t\n\v\f\r", str[0]))
			return (i);
		if (str[0] != symbol)
			i++;
		str++;
	}
	return (i);
}

/*
 * child function in extract_vars,
 * copy src to dest, skips when encounter double quote "
 * stop copy when encounter spaces ' ' 
 */
void	copy_vars(char *dest, char *src, int len)
{
	int		x;
	int		flag;
	char	symbol;

	if (!dest || !src)
		return ;
	x = 0;
	flag = 0;
	symbol = '\0';
	while (src[0] && x < len)
	{
		update_flag_quote(src, "\'\"", &symbol, &flag);
		if (src[0] != symbol)
			dest[x++] = src[0];
		src++;
	}
	dest[x] = '\0';
}

/*
 * child function in check_replace_dup,
 * overwrites existing var entry in linked list
 */
static int	overwrite_existing_var(t_env *head, char *str, int export_id)
{
	free(head->content);
	if (ft_strchr(str, '=') + 1)
		head->content = ft_strdup(ft_strchr(str, '=') + 1);
	if (head->exported < 1 && export_id >= 1)
		head->exported = export_id;
	else if (head->exported == 1)
		head->exported = 2;
	return (1);
}

/*
 * child function in extract_vars,
 * search for *name in var_name t_env linked list,
 * new= the entire var_assignment string (eg var=1234)
 * replace data & sets flag to 1 if duplicate found
 */
int	check_replace_dup(t_env *vars, char *name, char *new, int export_id)
{
	size_t	len;
	int		flag;

	flag = 0;
	while (vars && !flag)
	{
		len = 0;
		while (name[len] && !is_target(" \t\n\v\f\r", name[len]))
			len++;
		if (ft_strlen((*vars).env) > len)
			len = ft_strlen((*vars).env);
		if (ft_strncmp(vars->env, name, len) == 0 && !is_target(new, '='))
		{
			flag = 1;
			if (vars->exported == 0)
				vars->exported = 2;
		}
		else if (ft_strncmp(vars->env, name, len) == 0 && is_target(new, '='))
			flag = overwrite_existing_var(vars, new, export_id);
		vars = vars->next;
	}
	return (flag);
}
