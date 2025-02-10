/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:10:46 by hsim              #+#    #+#             */
/*   Updated: 2025/02/10 17:36:49 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

int	is_target(char *str, char c)
{
	while (str[0])
	{
		if (str[0] == c)
			return (1);
		str++;
	}
	return (0);
}

/* hello w\0*/

/*
 * counts the number of words in the provided str 
 * set = set of delimiiters
 * str = the entire string for scanning
 */
int	count_str(char *str, char *set)
{
	int		wc;

	wc = 0;
	while (str[0])
	{
		if (str[1] && is_target(set, str[1]) && \
			!is_target(set, str[0]))
			wc++;
		else if (str[1] == '\0' && !is_target(set, str[0]))
			wc++;
		str++;
	}
	return (wc);
}

/*
 * set = set of delimiters (" 	\n\v\f\r")
 * counts the number of characters and stop when delimiters detected
 */
int	count_chr(char *str, char *set)
{
	int	count;

	count = 0;
	while (str[0] && !is_target(set, str[0]))
	{
		count++;
		str++;
	}
	return (count);
}

/*
 * set = set of delimiters: " \t\n\v\f\r"
 * splits string into individual char* when *set is detected
 */
char	**ft_split_shell(char *str, char *set)
{
	char	**res;
	int		i;
	int		x;

	if (!str || !set)
		return (NULL);
	while (str[0] && is_target(set, str[0]))
		str++;
	i = 0;
	res = (char **)malloc(sizeof(char *) * (count_str(str, set) + 1));
	while (str[0] && count_str(str, set))
	{
		x = 0;
		res[i] = (char *)malloc(sizeof(char) * (count_chr(str, set) + 1));
		while (count_chr(str, set))
			res[i][x++] = *str++;
		res[i][x] = '\0';
		while (is_target(set, str[0]))
			str++;
		i++;
	}
	res[i] = NULL;
	return (res);
}
