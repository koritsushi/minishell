/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars_write.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:02:51 by hsim              #+#    #+#             */
/*   Updated: 2025/04/09 07:41:00 by hsim             ###   ########.fr       */
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
	int	f_equal_sign;

	i = 0;
	f_equal_sign = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			f_equal_sign = 1;
		if (f_equal_sign && (str[i] == '\'' || str[i] == '\"'))
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
 * copies src to dest, except when encountered double quote sign " (skips)
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
	// symbol = '\0';
	/*debug*/printf("copy_vars:src:%s, len:%d\n", src, len);
	while (src[0] && x < len)
	{
		/* 'po"$var' "p'$var" */
		update_flag_quote(src, &symbol, &flag);
		// if (src[0] == symbol && symbol == '\'')
		// if (!flag && src[0] == '\"')
		// {
		// 	symbol = src[0];
		// 	flag = 1;
		// }
		if (src[0] != symbol || (src[0] == symbol && symbol == '\''))
			dest[x++] = src[0];
		/*debug*/printf("copy_vars:%s.\n", dest);
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
	// /*debug*/printf("overwrite_existing_var:found! str:%s\n", (char *)head->content);
	free(head->content);
	/*overwrite*/
	/*debug*/printf("overwrite_existing_var:str:%s.\n", str);
	/*debug*/printf("overwrite_existing_var:strchr:%s.\n", ft_strchr(str, '=') + 1);
	if (ft_strchr(str, '=') + 1)
		head->content = ft_strdup(ft_strchr(str, '=') + 1);
	// head->content = ft_strdup(str);
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
	// char	**tmp;
	int		flag;

	flag = 0;
	while (vars && !flag)
	{
		len = 0;
		// tmp = ft_split_shell(vars->content, "=");
		/*debug*/printf("check_replace_dup name:%s, %s.\n", (*vars).env, name);
		while (name[len] && !is_target(" \t\n\v\f\r", name[len]))
			len++;
		/*debug*/printf("h:%s, %zu %zu\n", name, ft_strlen((*vars).env), len);
		if (ft_strlen((*vars).env) > len)
			len = ft_strlen((*vars).env);
		if (ft_strncmp(vars->env, name, len) == 0 && !is_target(new, '='))
		{
			// if exists but no content assigned
			flag = 1;
			if (vars->exported == 0)
				vars->exported = 2;
		}
		else if (ft_strncmp(vars->env, name, len) == 0 && is_target(new, '='))
			flag = overwrite_existing_var(vars, new, export_id);
		// free_chr_ptr((void **)tmp);
		vars = vars->next;
	}
	return (flag);
}