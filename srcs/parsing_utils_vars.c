/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:12:43 by hsim              #+#    #+#             */
/*   Updated: 2025/04/12 16:31:05 by hsim             ###   ########.fr       */
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
			// /*debug*/printf("\nbf_new=%s, str[0]=%c\n", str + 1, str[0]);
			str = skip_if_quote(str, str[0], 0); //wont it still skip regardless equal sign
			/*debug*/printf("find_next_var:skip=%s\n\n", str);
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
 * child function in extract_vars,
 * adds new var entry to the end of linked list
 * updates export_id to respective values
 * uses malloc
 */
static void	add_var_entry(t_env **vars, char *name, char *new, int export_id)
{
	t_env	*lst;

	/*if !found && !flag*/
	/*debug*/printf("add_var_entry:ent:content:\033[96m%s\033[0m.\n", new);
	lst = ft_lstnew_sh(name, new, export_id);
	ft_lstadd_back_sh(vars, lst);

	/*debug*/lst = ft_lstlast_sh(*vars);
	/*debug*/printf("add_var_entry:env:\033[93m%s\033[0m.\n", lst->env);
}

// 18 lines!
/*
 * child function in process_vars,
 * searches & replace duplicate var name in linked list, 
 * or add new var entry to list
 */
void	extract_vars(t_env **vars, char *str, int export_id)
{
	char	*name;
	char	*new;

	/* scan through string */
	/* search for name in linked list, if found, replace */
	/*debug*/printf("extract_vars:ent:\033[93m%s\033[0m.\n", str);
	while (str && str[0])
	{
		str = skip_spaces(str, " \t\n\v\f\r");
		if (!get_var_name(&name, str))
			return ;

		if (is_valid_var_name(&name, export_id))
		{
			/*debug*/printf("var_name=%s, var_len=%d+1, str=%s\n", name, count_malloc_vars(str), str);
			malloc_chr_ptr(&new, count_malloc_vars(str) + 1);
			copy_vars(new, str, count_malloc_vars(str));
			// ft_strlcpy(new, str, count_malloc_vars(str) + 1);
			/*debug*/printf("\033[93mcopy_vars:\033[0mfinal:%s\n", new);
			// /*debug*/printf("---------\ncheck_replace_dup:\n");
			// /*debug*/printf("---------\n");

			if (!check_replace_dup(*vars, name, new, export_id))
				add_var_entry(vars, name, new, export_id);
			free(new);
		}
		free(name);
		str = find_next_var(str);
		// if (str && str[0])
		// /*debug*/printf("find_next_var: str=\033[92m%s\033[0m.\n", str);
	}
}
