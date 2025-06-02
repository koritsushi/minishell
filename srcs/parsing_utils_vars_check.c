/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:10:01 by hsim              #+#    #+#             */
/*   Updated: 2025/06/02 15:12:12 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* syntax checking for variable assignments (var=some_data) */

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
		if ((flag && str[len] && is_target(" \t\n\v\f\r", str[len])) || \
(!flag && (str[len] == '\0' || is_target(" \t\n\v\f\r", str[len]))))
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
 * child function in has_non_var
 * joins & copies remaining text
 */
static void	copy_leftover(char **str, char **fin)
{
	int		k;
	char	*tmp;
	char	*tmp2;
	char	*final;

	k = 0;
	if (!fin || !fin[0])
		return ;
	final = ft_strdup(fin[k]);
	while (fin[k] && fin[k + 1])
	{
		tmp = ft_strjoin(" ", fin[k + 1]);
		tmp2 = ft_strjoin(final, tmp);
		free_multiple_ptr_single(final, tmp, NULL);
		final = ft_strdup(tmp2);
		free(tmp2);
		k++;
	}
	free(*str);
	*str = final;
}

/*
 * child function in check_var_syntax
 * breaks check if detected keyword: export 'export' "export"
 * checks if str doesnt have '=' (valid_var)
 */
static int	has_non_var(char **str)
{
	int		i;
	int		res;
	char	*new;
	char	**fin;

	new = skip_redir(*str);
	fin = ft_split_shell(new, " \t\n\v\f\r");
	res = 0;
	i = -1;
	while (fin && fin[++i] && !res)
	{
		if (!is_target(fin[i], '=') || \
(!ft_isalpha(fin[i][0]) && fin[i][0] != '_'))
		{
			copy_leftover(str, &fin[i]);
			if (valid_export_keyword(fin[i], 0) && fin[i + 1])
				break ;
			res = 1;
		}
	}
	free_chr_ptr((void **)fin);
	return (res);
}

/*
 * child function in get_variable,
 * checks if variable assigned syntax formatted correctly
 * & trims accordingly if invalid syntax found, eg:
 * '1var=x var=123 cmd' will be trimmed to 'cmd'
 * update flag=1 if starts with non_alpha
 */
int	check_var_syntax(char **str)
{
	char	*new;

	if (has_non_var(str))
		return (0);
	new = *str;
	while (new && new[0])
	{
		if (new[1] == '=' && \
((new[0] && is_target(" \t\n\v\f\r<>|&", new[0])) || \
(new[2] && is_target(" \t\n\v\f\r<>|&", new[2]))))
			return \
(ft_perror_fd("🚨 Syntax error! spaces before or after '='!\n", 2, 0));
		else if (new[1] == '=' && (new[2] == '\'' || new[2] == '\"'))
			new = skip_if_quote(new + 2, new[2], 1);
		if (new)
			new++;
	}
	return (1);
}
