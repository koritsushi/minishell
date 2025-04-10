/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:12:43 by hsim              #+#    #+#             */
/*   Updated: 2025/04/09 07:39:25 by hsim             ###   ########.fr       */
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
int	get_var_name(char **dest, char *str)
{
	char	*new;
	int		len;

	// /*debug*/printf("------\nget_var_name:\n");
	len = 0;
	new = skip_spaces(str, " \t\n\v\f\r"); //optional
	if (!new[0])
		return (0);
	while (new[len] && new[len] != '=')
		len++;
	/*debug*/printf("get_var_name:len=%d, leftover=%s.\n", len, &new[len]);
	if (new && malloc_chr_ptr(dest, (len + 1)))
		ft_strlcpy(*dest, new, len + 1);
	/*debug*/printf("get_var_name:new_bf=%s.\n", new);
	if (new[len] == '=')
		new += 1;
	new += len;
	/*debug*/printf("get_var_name:af:%s.\n", new);
	if (new[0] == '$' && new[1] && is_self_assigned(new, *dest)) // if $var
	{
		free(*dest);
		return (0);
	}
	/*debug*/printf("get_var_name:copied name!\033[93m%s\033[0m.\n", *dest);
	return (1);
}

/*
 * child function in extract_vars
 * trunc current variable to the beginning of next variable
 * if encounter ' ", skip; if encounter spaces, break
 */
char	*find_next_var(char *str)
{
	int	f_equal_sign;

	f_equal_sign = 0;
	while (str && str[0])
	{
		if (str[0] == '=')
			f_equal_sign = 1;
		if (str[0] == '\'' || str[0] == '"')
		{
			// /*debug*/printf("\nbf_new=%s, str[0]=%c\n", str + 1, str[0]);
			// str = skip_if_quote(str, str[0], 1);
			str = skip_if_quote(str, str[0], 0);
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
 * child function in is_valid_var_name
 * checks if there are spaces within var_name with quote mark ' "
 * eg 'var ' "var "
 */
static int	spaces_in_quote(char *str)
{
	int		flag;
	char	symbol;

	flag = 0;
	while (str && str[0] && !is_target(" \t\n\v\f\r", str[0]))
	{
		update_flag_quote(str, &symbol, &flag);
		if (flag && str[1] && is_target(" \t\n\v\f\r", str[1]))
			return (ft_perror_fd \
			("🚨 Error! Spaces detected in variable name\n", 2, 1));	
		str++;
	}
	return (0);
}

/*
 * child function in extract_vars
 * checks if str starts from non-alphabets && no '='
 * or if str contains any non-alphabets & non-numbers
 */
static int	is_valid_var_name(char **str, int export_id)
{
	char	*name;
	
	/*debug*/printf("is_valid_var_name:ent:%s.\n", *str);
	/*debug*/printf("is_valid_var_name:export_id:%d.\n", export_id);
	if (valid_export_keyword((*str), 0) || (export_id && spaces_in_quote((*str))))
		return (0);
	if (export_id) //optimize here
	{
		quote_removal(str);
		/*debug*/printf("is_valid_var_name:quote:%s.\n", *str);
	}
	name = *str;
	if (!ft_isalpha(name[0]))
		return (ft_perror_fd \
		("🚨 Error! Variable name should start with alphabet\n", 2, 0));
	while (name[0] && !is_target(" \t\n\v\f\r", name[0]))
	{
		/*debug*/printf("is_valid_var_name:while:%s.\n", name);
		if (!ft_isalnum(name[0]))
			return (ft_perror_fd \
			("🚨 Error! Symbols detected in variable name\n", 2, 0));
		name++;
		
		/* normal encounter spaces -> return 1 */
		/* if ' " on and encounter spaces || !alnum -> return 0 */

		/* non-export: have non-alnum */
		/* export: no ' " , have non-alnum */
		/* export: have spaces within ' ", error */
		/* export: have non-alnum within ' ", error */

		/* 'var t'*/
		/* if export_id > 0, has ' ", while flag ' " on met spaces */
	}
	return (1);
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
	/*debug*/printf("add_var_entry:ent:content:\033[96m%s\033[0m.\n", new);
	// ft_lstadd_back_sh(vars, ft_lstnew_sh(ft_strdup(new)));
	ft_lstadd_back_sh(vars, ft_lstnew_sh(new));
	tmp = ft_lstlast_sh(*vars);
	/*debug*/printf("add_var_entry:env:\033[93m%s\033[0m.\n", tmp->env);
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
	(void)	vars;
	char	*name;
	char	*new;

	/* scan through string */
	/* search for name in linked list, if found, replace */
	while (str && str[0])
	{
		/*debug*/printf("extract_vars:ent:\033[93m%s\033[0m.\n", str);
		str = skip_spaces(str, " \t\n\v\f\r");
		if (!get_var_name(&name, str))
			return ;

		if (is_valid_var_name(&name, export_id))
		{
			/*debug*/printf("var_name=%s, var_len=%d+1, str=%s\n", name, count_malloc_vars(str), str);
			malloc_chr_ptr(&new, count_malloc_vars(str) + 1);
			copy_vars(new, str, count_malloc_vars(str));
			// ft_strlcpy(new, str, count_malloc_vars(str) + 1);
			/*debug*/printf("copy_vars:final:%s\n", new);
			// /*debug*/printf("---------\ncheck_replace_dup:\n");

			// flag_duplicate = check_replace_dup(*vars, name, new, export_id);
			// /*debug*/printf("---------\n");

			// if (flag_duplicate == 0) // if no duplicates
			if (!check_replace_dup(*vars, name, new, export_id))
				add_var_entry(vars, new, export_id);
			free(new);
		}
		free(name);
		str = find_next_var(str);
		// if (str && str[0])
		// /*debug*/printf("find_next_var: str=\033[92m%s\033[0m.\n", str);
	}
}
