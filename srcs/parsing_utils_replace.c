/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_replace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:35:28 by hsim              #+#    #+#             */
/*   Updated: 2025/03/18 22:15:57 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

/*
 * child function in replace_var_space, 
 * if is empty spaces after last pipe '|', replace last pipe with spaces ' '
 */
// void	replace_last_pipe(char *str)
// {
// 	char	*new;

// 	if (ft_strrchr(str, '|'))
// 	{
// 		new = ft_strrchr(str, '|');
// 		/*debug*/printf("end_:\033[90m%s\033[0m.\n", new);
// 		while (new[1] && is_target(" \t\n\v\f\r", new[1]))
// 			new++;
// 		if (new[1] == '\0')
// 		{
// 			new = ft_strrchr(str, '|');
// 			new[0] = ' ';
// 		}
// 	}
// }

/*
 * child function in replace_var_space,
 * writes entire quoted area to spaces ' ' if quote symbol ' or " detected
 */
static void	replace_quote_space(char **str)
{
	char	*new;
	int		i;

	new = *str;
	i = 0;
	if (new[0] && is_target("'\"", new[0]))
	{
		i = (int)(ft_strchr(&new[1], new[0]) - &new[0]);
		while (i >= 0)
			new[i--] = ' ';
		// /*debug*/printf("i=%d, %s\n", i, new);
	}
}

/*
 * child function in replace_var_space
 * checks if 1st word has '=', if none, skips to the next pipe '|'
 * skips all spaces before start checking
 */
char	*skip_if_no_assign(char *str)
{
	char	*new;

	if (!str)
		return (str);
	/* echo var=0 | ^var=9 */
		/* if 1st str has no '=', skip to next pipe */
		/* if no '|', exit */
		/* skip if '" */
	new = skip_spaces(str, " \t\n\v\f\r");
	while (new[0] && !is_target(" \t\n\v\f\r|", new[0]))
	{
		if (new[0] == '=')
			return (str);
		new++;
	}
	new = ft_strchr(new, '|');
	if (new)
		return (new + 1);
	return (new);
}

// 23 lines!
/*
 * child function in replace_var_space
 * starts overwrite var assignment (eg var=90) with space ' '
 * if var name is valid (var[0] starts with alphabet)
 */
static char	*overwrite_with_space(char *str, int *i)
{
	char	*new;

	if (!str)
		return (str);
	new = skip_spaces(str - (*i), " \t\n\v\f\r");
	// /*debug*/printf("overwrite_with_space:%s. %d\n", new, *i);
	if (!ft_isalpha(new[0]) && new[0] != '|')
	{
		new = skip_if_symbol(new, 'c', 'c');
		*i = 0;
		return (skip_if_symbol(new, 'c', 'c'));
		// /*debug*/printf("overwrite_with_space:!alpha:%s\n", new);
		// return (new);
	}
	while (new && new[0] && !is_target(" \t\n\v\f\r<>|", new[0]))
	{
		/* vars='op' cmd1 -k -l */
		/* cmd1 -k -l vars='op'*/
		if (is_target("\'\"", new[0]))
			replace_quote_space(&new);
		else if (!is_target(" \t\n\v\f\r", new[0]))
			new[0] = ' ';
		// if (new && new[0])
			// /*debug*/printf("half:%s\n", new);
		new++;
	}
	new = skip_spaces(new, " \t\n\v\f\r");
	/* check if next word !has '=' || start from non-alpha */
	// if (new && new[0] == '|')
		// new[0] = ' ';
	*i = 0;
	return (new);
}

char	*overwrite_export_line(char *str)
{
	if (!str)
		return (str);
	while (str[0] && !is_target("|", str[0]))
		*str++ = ' ';
	return (str);
}

// 22 lines!!
/* overwrites var assignment in str (eg var=123) to blank space ' ' */
void	replace_var_space(char *str)
{
	char	*new;
	int		i;

	/* searches location of '=' */
	/* reverse search the space before '=' */
	/* fill all with ' ' until isalnum || !| && spaces*/
	/* var=0, var='0', var="0", ^var=0, cmd, 'cmd' */
	/* skip if ' " , skip if no '=', skip if !alpha */

	new = str;
	i = 0;
	// /*debug*/printf("replace_var_space:enter:%s\n", new);
	while (new && new[0])
	{
	// 	/* reset i count if encounter spaces/'" */
		// if (ft_strncmp(new, "export", 6) == 0)
			// new = overwrite_export_line(new);
			/* overwrite_spaces_up_to_pipe_| */
		// else
			new = skip_if_no_assign(new);
		/*debug*/printf("replace_var_space:skip:%s\n", new);
		if (new && new[0] && is_target(" \'\"\t\n\v\f\r", new[0]))
			i = 0;
		if (new && new[0] && is_target("\'\"", new[0]))
		{
			new = skip_if_quote(new, new[0], 1);
			if (new[0] && !is_target("\'\"", new[0]))
				new -= 1;
		}
		else if (new && new[0] == '=')
			new = overwrite_with_space(new, &i);
			// /*debug*/printf("replace_var_space:%s. %d\n", new, i);
		i++;
		if (new)
			new++;
	}
	// replace_last_pipe(str);
}
