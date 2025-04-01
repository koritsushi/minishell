/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:12:43 by hsim              #+#    #+#             */
/*   Updated: 2025/04/01 10:04:46 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

/*
 * child function in get_var_name,
 * checks if var_name is same as assigned content (eg var=$var)
 */
static int	is_self_assigned(char *str, char *name)
{
	int		flag;
	size_t	len;
	char	*check;

	flag = 0;
	len = 0;
	while (str[len + 1] && !is_target(" \t\n\v\f\r", str[len + 1]))
		len++;
	if (malloc_chr_ptr(&check, (len + 1)))
		ft_strlcpy(check, str + 1, len + 1);
	/*debug*/printf("compare:%s\n", check);
	len = ft_strlen(name);
	if (ft_strlen(check) > len)
		len = ft_strlen(check);
	if (ft_strncmp(name, check, len) == 0)
		flag = 1;
	free(check);
	return (flag);
}

/*
 * child function in extract_vars,
 * searches in str for var_name & save til before '='
 * if var is self assigned (var=$var), frees & return
 * uses malloc
 */
int get_var_name(char **dest, char *str)
{
	char	*new;
	int		len;

	// /*debug*/printf("------\nget_var_name:\n");
	len = 0;
	new = skip_spaces(str, " \t\n\v\f\r"); //optional
	while (new[len] && new[len] != '=')
		len++;
	/*debug*/printf("len=%d, leftover=%s.\n", len, &new[len]);
	if (new && malloc_chr_ptr(dest, (len + 1)))
		ft_strlcpy(*dest, new, len + 1);
	/*debug*/printf("new_bf=%s.\n", new);
	if (new[len] == '=')
		new += 1;
	new += len;
	/*debug*/printf("get_var_name:af:%s.\n", new);
	if (new[0] == '$' && new[1] && is_self_assigned(new, *dest))
	{
		free(*dest);
		return (0);
	}
	return (1);
}

/*
 * child function in extract_vars
 * trunc current variable to the beginning of next variable
 * if encounter ' ", skip; if encounter spaces, break
 */
char	*find_next_var(char *str)
{
	while (str && str[0])
	{
		if (str[0] == '\'' || str[0] == '"')
		{
			// /*debug*/printf("\nbf_new=%s, str[0]=%c\n", str + 1, str[0]);
			str = skip_if_quote(str, str[0], 1);
			// /*debug*/printf("new=%s\n\n", str);
			if (str[0] == '\'' || str[0] == '"')
				return (str + 1);
			return (str);
		}
		else if (str[0] && is_target(" \t\n\v\f\r", str[0]))
			return (skip_spaces(str, " \t\n\v\f\r"));
		str++;
	}
	return (NULL);
}

/*
 * child function in extract_vars,
 * adds new var entry to the end of linked list
 * updates export_id to respective values
 */
static void	add_var_entry(t_env **vars, char *new, int export_id)
{
	t_env *tmp;

	/*if !found && !flag*/
	// /*debug*/printf("saved: new=\033[96m%s\033[0m.\n", new);
	ft_lstadd_back_sh(vars, ft_lstnew_sh(ft_strdup(new)));
	tmp = ft_lstlast_sh(*vars);
	tmp->exported = export_id;
	if (!is_target(new, '='))
		tmp->exported = 1;
}

// 18 lines!
/*
 * child function in process_vars,
 * searches & replace duplicate var name in linked list, 
 * or add new var entry to list
 */
void	extract_vars(t_env **vars, char *str, int export_id)
{
	int		flag;
	char	*name;
	char	*new;

	/* scan through string */
	/* search for name in linked list, if found, replace */
	while (str && str[0])
	{
		flag = 0;
		str = skip_spaces(str, " \t\n\v\f\r");
		/* get_var_name */
		if (!get_var_name(&name, str))
			return ;
		/* if assignment content = $var_name, break */
		/*count & copy variable name*/
		/*debug*/printf("var_name=%s, var_len=%d+1\n", name, count_malloc_vars(str));
		malloc_chr_ptr(&new, count_malloc_vars(str) + 1);
		copy_vars(new, str, count_malloc_vars(str));
		// /*debug*/printf("copy_vars:%s\n", new);
		// /*debug*/printf("---------\ncheck_replace_dup:\n");
		flag = check_replace_dup(*vars, name, new, export_id);
		// /*debug*/printf("---------\n");
		if (flag == 0) // if no duplicates
			add_var_entry(vars, new, export_id);
		/*free variable name*/
		free_multiple_ptr_single(2, new, name);
		str = find_next_var(str);
		// if (str && str[0])
		// /*debug*/printf("find_next_var: str=\033[92m%s\033[0m.\n", str);
	}
}
