/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_check_vars.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:10:01 by hsim              #+#    #+#             */
/*   Updated: 2025/04/01 09:55:51 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

/* syntax checking for variable assignments (var=some_data) */

/*
 * child function in check_var_syntax
 * checks str if has both < and > redirs
 */
// int	has_mix_redirs(char *str)
// {
// 	int	flag;

// 	flag = 0;
// 	if (str && str[0] && is_target(str, '<'))
// 		flag = 1;
// 	if (str && str[0] && is_target(str, '>'))
// 		return (flag == 1);
// 	return (0);
// }

/*
 * child function in check_var_syntax
 * checks if any word/variable name starts from non-alphabets && doesnt have '='
 * changes flag value if true
 */
static int	has_non_alpha(char *str)
{
	char	*new;
	char	**tmp;
	char	**fin;
	int		i;
	int		res;

	new = skip_redirs(str);
	tmp = ft_split_shell(new, "<>");
	fin = ft_split_shell(tmp[0], " \t\n\v\f\r");
	res = 0;
	i = -1;
	while (fin && fin[++i] && !res)
	{
		if (ft_strncmp(fin[i], "export", 6) == 0)
			break ;
		if ((fin[i][0] && !ft_isalpha(fin[i][0])) || !is_target(fin[i], '='))
		{
			res = 1;
			/*debug*/printf("has_non_alpha:%s\n", fin[i]);
		}
	}
	/* var=90 var2=56 ^var=6 */
	/* ^var=6 */
	free_multiple_ptr(2, tmp, fin);
	return (res);
}

// 17 lines!
/*
 * child function in get_variable,
 * checks if variable assigned syntax formatted correctly
 * update flag=1 if starts with non_alpha
 */
int	check_var_syntax(char *str, int *flag)
{
	char	*new;

	/* mix in/out files */
	/* has other cmds */
	/* syntax incorrect: have spaces before/after '=' */
	/* '=' happen before ' " */
	/* mix in/out files */
	// if (has_mix_redirs(new) || has_non_alpha(new))
	new = str;
	if (has_non_alpha(new))
		*flag = 1;
	/* skips infile outfile at head */
	// new = skip_redirs(new);
	while (new && new[0] && !(*flag))
	{
		if (new[1] == '=' && \
			((new[0] && is_target(" \t\n\v\f\r<>|&", new[0])) || \
			(new[2] && is_target(" \t\n\v\f\r<>|&", new[2]))))
			return (ft_perror_fd("🚨 Syntax error! spaces before or after '='!\n", 2, 0));
		else if (new[1] == '=' && (new[2] == '\'' || new[2] == '\"'))
			new = skip_if_quote(new + 2, new[2], 1);
		new++;
	}
	return (1);
}
