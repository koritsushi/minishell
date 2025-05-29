/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_brace_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:40:04 by hsim              #+#    #+#             */
/*   Updated: 2025/05/29 18:37:02 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

/*
 * checks if passed str has {,}  (valid brace content)
 * breaks if encounter spaces ' '
 */
int	has_valid_brace_content(char *str)
{
	int		flag;

	if (!str)
		return (0);
	flag = 0;
	while (str && str[0] && !is_target(" \t\n\v\f\r", str[0]))
	{
		if (str[0] == '{' && str[1] && is_valid_brace_start(str + 1))
			break ;
		else if (is_target("\'\"", str[0]))
			str = ft_strchr(str + 1, str[0]);
		else if (str)
			str++;
	}
	if (str && str[0] && !is_target(" \t\n\v\f\r", str[0]))
		flag = 1;
	return (flag);
}
