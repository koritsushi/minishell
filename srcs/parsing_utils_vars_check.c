/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:10:01 by hsim              #+#    #+#             */
/*   Updated: 2025/04/06 13:40:42 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* syntax checking for variable assignments (var=some_data) */

#include "includes/parsing.h"

/*
 * child function in is_valid_var_name
 * checks if str contains any non-alphabets & numbers
 * returns 0 if detect non-alnum
 * str=tmp[0]
 */
static int	check_if_non_alnum(char *str)
{
	int		i;
	int		res;
	char	**tmp;

	res = 1;
	tmp = ft_split_shell(str, "=");
	i = -1;
	if (ft_strncmp(tmp[0], "export", 6) == 0 && skip_if_symbol(tmp[0], 'c', 'c'))
	{
		i = skip_if_symbol(tmp[0], 'c', 'c') - tmp[0];
		/*debug*/printf("check_if_non_alnum:ent:%s.\n", &tmp[0][i]);
	}
	while (tmp[0][++i] && res)
	{
		/*debug*/printf("check_if_non_alnum:while_ent:%s.\n", &tmp[0][i]);
		if (!ft_isalnum(tmp[0][i]))
			res = 0;
	}
	free_chr_ptr((void **)tmp);
	return (res);

}

/*
 * child function in check_var_syntax
 * checks if str starts from non-alphabets && doesnt have '=' (valid_var_name)
 * or if str contains any non-alphabets & numbers
 * changes flag value if true
 */
static int	is_valid_var_name(char *str)
{
	char	*new;
	char	**tmp;
	char	**fin;
	int		i;
	int		res;

	new = skip_redirs(str);
	tmp = ft_split_shell(new, "<>");
	fin = ft_split_shell(tmp[0], " \t\n\v\f\r");
	res = 1;
	i = -1;
	while (fin && fin[++i] && !res)
	{
		/*debug*/printf("is_valid_var_name:ent:%s.\n", fin[i]);
		if (ft_strncmp(fin[i], "export", 6) == 0)
			break ;
		if ((fin[i][0] && !ft_isalpha(fin[i][0])) || !is_target(fin[i], '='))
		{
			res = 0;
			/*debug*/printf("is_valid_var_name:found!%s\n", fin[i]);
		}
	}
	if (res)
		res = check_if_non_alnum(tmp[0]);
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
	// if (has_mix_redirs(new) || is_valid_var_name(new))
	new = str;
	if (!is_valid_var_name(new))
		*flag = 1;
	// return (0);
	/* skips infile outfile at head */
	// new = skip_redirs(new);
	while (new && new[0] && !(*flag)) //export & default can use flag != 1
	{
		/*debug*/printf("check_var_syntax:ent:%s\n", new);
		if (new[1] == '=' && \
			((new[0] && is_target(" \t\n\v\f\r<>|&", new[0])) || \
			(new[2] && is_target(" \t\n\v\f\r<>|&", new[2]))))
			return (ft_perror_fd("🚨 Syntax error! spaces before or after '='!\n", 2, 0));
		// else if (new[1] == '=' && valid_var_name())
		// 	return (0);
		else if (new[1] == '=' && (new[2] == '\'' || new[2] == '\"'))
			new = skip_if_quote(new + 2, new[2], 1);
		new++;
	}
	// if (*flag)
	// 	return (0);
	return (1);
}
