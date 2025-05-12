/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:57:56 by hsim              #+#    #+#             */
/*   Updated: 2025/05/12 11:48:35 by hsim             ###   ########.fr       */
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
 * child function in get_var_name,
 * breaks if encounter '=' or spaces(when quote is not detected)
 * counts & return len
 */
static int	count_var_name(char *new)
{
	int		len;
	int		flag;
	char	symbol;
	
	len = 0;
	flag = 0;
	while (new[len])
	{
		update_flag_quote(&new[len], &symbol, &flag);
		if (new[len] && ((new[len] == '=') || \
(!flag && is_target(" \t\n\v\f\r", new[len]))))
			break;
		len++;
	}
	return (len);
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
	len = count_var_name(new);

	/*debug*/printf("get_var_name:len:%d, leftover:%s.\n", len, &new[len]);
	if (new && malloc_chr_ptr(dest, (len + 1)))
		ft_strlcpy(*dest, new, len + 1);
	/*debug*/printf("get_var_name:new_bf=%s.\n", new);

	/* check if is_self_assigned */
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

// 17 lines!
/*
 * child function in extract_vars
 * checks if str starts from non-alphabets && no '='
 * or if str contains any non-alphabets & non-numbers
 */
int	is_valid_var_name(char **str, int export_id)
{
	char	*name;

	/*debug*/printf("is_valid_var_name:ent:%s.\n", *str);
	/*debug*/printf("is_valid_var_name:export_id:%d.\n", export_id);
	// if (valid_export_keyword((*str), 0) || (export_id && spaces_in_quote((*str))))
	if (export_id && spaces_in_quote((*str)))
		return (0);
	if (export_id)
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
