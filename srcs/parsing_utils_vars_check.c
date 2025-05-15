/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:10:01 by hsim              #+#    #+#             */
/*   Updated: 2025/05/15 12:27:33 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* syntax checking for variable assignments (var=some_data) */

#include "includes/parsing.h"

void	copy_leftover(char **str, char **fin)
{
	int		k;
	char	*tmp;
	char	*tmp2;
	char	*final;

	k = 0;
	if (!fin || !fin[0])
		return ;
	// s3 = str1 + str2
	// s3 = s3 + str4
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

//21 lines
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

	new = skip_redirs(*str);
	/*debug*/printf("has_non_var:skip:%s.\n", new);
	// tmp = ft_split_shell(new, "<>"); //maybe noneed
	fin = ft_split_shell(new, " \t\n\v\f\r");
	res = 0;
	i = -1;
	while (fin && fin[++i] && !res)
	{
		/*debug*/printf("has_non_var:ent:%s.\n", fin[i]);
		// if (valid_export_keyword(fin[i], 0)) // && has_more_str after export
		// {
		// 	/*debug*/printf("has_non_var:export! %d\n", res);
		// 	break ;
		// }
		if (!is_target(fin[i], '=') || !ft_isalpha(fin[i][0]))
		{
			// if export only, skip process_vars
			// v=1 export blbla -> res=0 (break)
			// v=1 export       -> res=1
			// v=1 cmd abe      -> res=1

			// copy n alloc the rest, 
			copy_leftover(str, &fin[i]);
			if (valid_export_keyword(fin[i], 0) && fin[i + 1])
				break ;
			res = 1;

			// var=123 var=56      : free later ( valid_var_syntax )
			// var=123 var=6 cmd   : trim
			// var=123 1var=6 cmd  : trim
			// var=123 cmd var=6   : trim to before cmd
	
			// /*debug*/printf("has_non_var:str!%s\n", *str);
			/*debug*/printf("has_non_var:found!%s\n", fin[i]);
		}
	}
	/* var=90 var2=56 ^var=6 */
	/* ^var=6 */
	free_chr_ptr((void **)fin);
	return (res);
}

// static int	has_non_var(char *str)
// {
// 	char	**tmp;
// 	char	**fin;
// 	int		i;
// 	int		res;

// 	str = skip_redirs(str);
// 	/*debug*/printf("has_non_var:skip:%s.\n", str);
// 	tmp = ft_split_shell(str, "<>");
// 	fin = ft_split_shell(tmp[0], " \t\n\v\f\r");
// 	res = 0;
// 	i = -1;
// 	while (fin && fin[++i] && !res)
// 	{
// 		/*debug*/printf("has_non_var:ent:%s.\n", fin[i]);
// 		if (valid_export_keyword(fin[i], 0)) // && has_more_str after export
// 		{
// 			/*debug*/printf("has_non_var:export! %d\n", res);
// 			break ;
// 		}
// 		if (!is_target(fin[i], '=') || !ft_isalpha(fin[i][0]))
// 		{
// 			res = 1;
// 			// copy n alloc the rest, 
// 			// if != export has_more_str, res = 1
// 			// return new str

// 			// var=123 var=56      : free later ( valid_var_syntax )
// 			// var=123 var=6 cmd   : trim
// 			// var=123 1var=6 cmd  : trim
// 			// var=123 cmd var=6   : trim to before cmd
	
// 			/*debug*/printf("has_non_var:found!%s\n", fin[i]);
// 		}
// 	}
// 	/* var=90 var2=56 ^var=6 */
// 	/* ^var=6 */
// 	free_multiple_ptr(tmp, fin, NULL);
// 	return (res);
// }

// 17 lines!
/*
 * child function in get_variable,
 * checks if variable assigned syntax formatted correctly
 * & trims accordingly if invalid syntax found, eg:
 * '1var=x var=123 cmd' will be trimmed to 'cmd'
 * update flag=1 if starts with non_alpha
 */
int	check_var_syntax(char **str)//, int *flag)
{
	char	*new;

	/* if no export && has_more_str , error! */
	if (has_non_var(str))
	{
		/*debug*/printf("check_var_syntax:\033[93mnon var detected!\033[0m\n");
		return (0);
	}

	new = *str;
	while (new && new[0])// && !(*flag)) //export & default can use flag != 1
	{
		// /*debug*/printf("check_var_syntax:ent:%s\n", new);
		if (new[1] == '=' && \
			((new[0] && is_target(" \t\n\v\f\r<>|&", new[0])) || \
			(new[2] && is_target(" \t\n\v\f\r<>|&", new[2]))))
			return (ft_perror_fd("🚨 Syntax error! spaces before or after '='!\n", 2, 0));
		else if (new[1] == '=' && (new[2] == '\'' || new[2] == '\"'))
			new = skip_if_quote(new + 2, new[2], 1);
		if (new)
			new++;
	}
	// if invalid_var_name
	return (1);
}
