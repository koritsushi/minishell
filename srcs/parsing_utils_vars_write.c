/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars_write.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:02:51 by hsim              #+#    #+#             */
/*   Updated: 2025/04/01 10:11:43 by hsim             ###   ########.fr       */
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
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			// printf("count_malloc_vars: i=%d, %s.\n", i, &str[i]);
			// printf("%d+1\n", (int)(ft_strchr(&str[i + 1], str[i]) - &str[i]));
			i += (int)(ft_strchr(&str[i + 1], str[i]) - &str[i]);
			if (str[i] == '\"')
				return (i + 1 - 2);
			return (i + 1);
		}
		else if (str[i] && is_target(" \t\n\v\f\r", str[i]))
			return (i);
		i++;
	}
	return (i);
}

/*
 * child function in extract_vars,
 * copies src to dest, skips when encountered double quote sign "
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
		// if (!flag && (src[0] == '\'' || src[0] == '\"'))
		if (!flag && src[0] == '\"')
		{
			symbol = src[0];
			flag = 1;
		}
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
	/*debug*/printf("check_replace_dup:found! str:%s\n", (char *)head->content);
	free(head->content);
	/*overwrite*/
	head->content = ft_strdup(str);
	/*debug*/printf("def:export_id:%d\n", export_id);
	if (head->exported < 1 && export_id >= 1)
		head->exported = export_id;
	else if (head->exported == 1)
		head->exported = 2;
	return (1);
}

// 24 lines
/*
 * child function in extract_vars,
 * search for var name in linked list,
 * replace data & sets flag to 1 if duplicate found
 */
int	check_replace_dup(t_env *vars, char *name, char *new, int export_id)
{
	size_t	len;
	char	**tmp;
	int		flag;

	flag = 0;
	while (vars && !flag)
	{
		len = 0;
		tmp = ft_split_shell(vars->content, "=");
		/*debug*/printf("check_replace_dup name:%s, %s.\n", tmp[0], name);
		while (name[len] && !is_target(" \t\n\v\f\r", name[len]))
			len++;
		/*debug*/printf("h:%s, %zu %zu\n", new, ft_strlen(tmp[0]), len);
		if (ft_strlen(tmp[0]) > len)
			len = ft_strlen(tmp[0]);
		if (ft_strncmp(vars->content, name, len) == 0 && !is_target(new, '='))
		{
			flag = 1;
			if (vars->exported == 0)
				vars->exported = 2;
		}
		else if (ft_strncmp(vars->content, name, len) == 0 && is_target(new, '='))
			flag = overwrite_existing_var(vars, new, export_id);
		free_chr_ptr((void **)tmp);
		vars = vars->next;
	}
	return (flag);
}