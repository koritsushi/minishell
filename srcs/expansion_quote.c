/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:30:48 by hsim              #+#    #+#             */
/*   Updated: 2025/05/03 08:29:25 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

/*
 * child function in quote_removal
 * counts correct amount for remalloc usage
 */
int	count_malloc_quote_removal(char *str)
{
	int		len;
	int		flag;
	char	symbol;

	len = 0;
	flag = 0;
	while (str && str[0])
	{
		if (!flag && is_target("\'\"", str[0]))
		{
			flag = 1;
			symbol = str[0];
		}
		else if (flag && str[0] == symbol)
			flag = 0;
		else
			len++;
		str++;
	}
	return (len);
}

void	expand_quote_removal(char *src, char *dest)
{
	int		x;
	int		flag;
	char	symbol;

	x = 0;
	flag = 0;
	symbol = '\0';
	while (src && src[0])
	{
		update_flag_quote(src, &symbol, &flag);
		if (src[0] != symbol)
			dest[x++] = src[0];
		src++;
	}
}
