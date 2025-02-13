/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:10:46 by hsim              #+#    #+#             */
/*   Updated: 2025/02/13 08:00:22 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/* checks if char c == members in str */
int	is_target(char *str, char c)
{
	if (!str)
		return (0);
	while (str[0])
	{
		if (str[0] == c)
			return (1);
		str++;
	}
	return (0);
}

/*
 * counts the number of words in the provided str 
 * set = set of delimiiters
 * str = the entire string for scanning
 */
int	count_str(char *str, char *set)
{
	int		wc;
	int		flag;

	wc = 0;
	flag = 0;
	if (str[0] && !is_target(set, str[0]))
		wc++;
	while (str[0])
	{
		if (flag == 0 && str[0] == '\'')
			flag = 1;
		else if (flag == 1 && str[0] == '\'')
			flag = 0;
		if (str[1] && !flag && is_target(set, str[0]) && \
			!is_target(set, str[1]))
			wc++;
		else if (str[1] && !flag && !is_target(set, str[0]) && \
			str[1] == '\'')
			wc++;
		str++;
	}
	return (wc);
}

/*
 * a combo function to increment stuff and set flag value
 * increment str++ & count++
 * if flag != -1, returns value set in flag
 */
static int	increment_val(int flag, int *count, char **str)
{
	(*count)++;
	if (str)
		(*str)++;
	if (flag != -1)
		return (flag);
	return (0);
}

/*
 * set = set of delimiters (" \t\n\v\f\r")
 * counts the number of characters and stop when delimiters detected
 */
int	count_chr(char *str, char *set, int *flag)
{
	int	count;

	count = 0;
	if (*flag == 0 && str[0] == '\'')
		*flag = increment_val(1, &count, &str);
	else if (*flag == 1 && str[0] == '\'')
	{
		*flag = 0;
		return (count + 1);
	}
	while (str[0] && *flag)
	{
		if (str[0] == '\'')
			return (count + 1);
		increment_val(-1, &count, &str);
	}
	while (str[0] && !(*flag) && !is_target(set, str[0]))// && str[0] != '\'')
		increment_val(-1, &count, &str);
	return (count);
}

/*
 * set = set of delimiters: " \t\n\v\f\r"
 * splits string into individual char* when *set is detected
 * if *set not found, will return back the str
 * uses malloc
 */
char	**ft_split_shell(char *str, char *set)
{
	char	**res;
	int		i;
	int		x;
	int		f;

	if (!str || !set)
		return (NULL);
	while (str[0] && is_target(set, str[0]))
		str++;
	i = 0;
	f = 0;
	res = (char **)malloc(sizeof(char *) * (count_str(str, set) + 1));
	while (str[0] && count_str(str, set))
	{
		x = 0;
		res[i] = (char *)malloc(sizeof(char) * (count_chr(str, set, &f) + 1));
		f = 0;
		while (count_chr(str, set, &f))
			res[i][x++] = *str++;
		res[i++][x] = '\0';
		while (is_target(set, str[0]))
			str++;
	}
	res[i] = NULL;
	return (res);
}
