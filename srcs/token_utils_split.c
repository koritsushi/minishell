/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:10:46 by hsim              #+#    #+#             */
/*   Updated: 2025/06/03 12:07:25 by hsim             ###   ########.fr       */
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
	char	symbol;

	wc = 0;
	flag = 0;
	symbol = '\0';
	if (str[0] && !is_target(set, str[0]))
		wc++;
	while (str[0])
	{
		if (str[1] && !flag && is_target(set, str[0]) && \
!is_target(set, str[1]))
			wc++;
		if (!is_target(set, '\"') && !is_target(set, '\''))
			update_flag_quote(str, "\'\"", &symbol, &flag);
		str++;
	}
	return (wc);
}

/*
 * a combo function to increment count & str and set flag value
 * increment str++ & count++
 * if flag != -1, returns value set in flag
 */
static int	increment_val(int flag, int *count, char **str)
{
	(*count)++;
	if (str && *str)
		(*str)++;
	if (flag != -1)
		return (flag);
	return (0);
}

/*
 * set = set of delimiters (" \t\n\v\f\r")
 * counts the number of characters and stop when delimiters detected
 * if flag == 1, ignore *set, else: stop upon *set
 */
static int	count_chr(char *str, char *set)
{
	int		flag;
	int		count;
	char	symbol;

	flag = 0;
	count = 0;
	symbol = '\0';
	while (str && str[0] && (!is_target(set, str[0]) || (flag == 1)))
	{
		if (flag == 0 && str[0] && is_target("'\'\"", str[0]) && \
!is_target(set, '\"') && !is_target(set, '\''))
			symbol = str[0];
		if (flag == 0 && str[0] == symbol)
			flag = 1;
		else if (flag == 1 && str[0] == symbol)
			flag = 0;
		if (flag && str[0])
			increment_val(-1, &count, &str);
		else if (!flag && str[0] && !is_target(set, str[0]))
			increment_val(-1, &count, &str);
	}
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
	int		count;

	if (!str || !set)
		return (NULL);
	i = 0;
	str = skip_spaces(str, set);
	res = (char **)malloc(sizeof(char *) * (count_str(str, set) + 1));
	while (str[0] && count_str(str, set))
	{
		count = count_chr(str, set);
		if (!malloc_chr_ptr(&res[i], count + 1))
		{
			ft_perror_fd("malloc_failed!\n", 2, 0);
			return (0);
		}
		ft_strlcpy(res[i++], str, count + 1);
		str = skip_spaces(str + count, set);
	}
	res[i] = NULL;
	return (res);
}
