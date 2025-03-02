/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_truncate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:26:21 by hsim              #+#    #+#             */
/*   Updated: 2025/03/02 17:39:16 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/* search for last occurence of char c up to len count, len=endpoint */
char	*search_rstr(char *str, char c, int len)
{
	// printf("end=%s\n", &str[len]);
	while (str[0] && --len >= 0)
	{
		if (str[len] == c)
		{
			if (str[len - 1] && str[len - 1] == c)
				return (&str[len - 1]);
			return (&str[len]);
		}
	}
	return (str);
}

/* 
 * child function for truncate_input
 * searches for '<' in str and returns pointer to the last infile '<' occured
 * eg. ... | cmd1 <infile | ...  truncates to start from ->  cmd1 <infile | ...
 */
static char	*truncate_infile_back(char *str)
{
	int		len;
	int		i;
	char	*new;

	i = 0;
	len = ft_strlen(str);
	while (str[0] && --len >= 0)
	{
		if (str[len] == '<')
		{
			new = search_rstr(str, '|', (ft_strlen(str) - i));
			if (new[0] == '|')
				return (new + 1);
			return (new);
		}
		i++;
	}
	return (str);
}

/*
 * child function to truncate_input
 * if str[0] == '<', truncates beginning of str to last occurence of '<'
 * truncate_infile_front
 */
static char	*truncate_infile_front(char *str)
{
	char	*new;

	new = search_rstr(str, '<', ft_strlen(str));
	return (new);
}

/* formats string and truncate to its last infile '<' sign */
char	*truncate_input(char *str)
{
	char	*new;

	new = skip_spaces(str, " \t\n\v\f\r");
	new = truncate_infile_back(new);
	new = skip_spaces(new, " \t\n\v\f\r");
	/*debug*/printf("trunc_tail=%s\n", new);
	if (new[0] == '<')
	{
		new = truncate_infile_front(new);
		/*debug*/printf("trunc_head=%s\n", new);
	}
	new = skip_spaces(new, " \t\n\v\f\r");
	return (new);
}
