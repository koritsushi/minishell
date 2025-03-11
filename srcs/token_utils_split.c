/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:10:46 by hsim              #+#    #+#             */
/*   Updated: 2025/03/11 14:28:35 by hsim             ###   ########.fr       */
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
		wc++; //if there's word, count
	while (str[0])
	{
		// /*debug*/printf("count_str_enter:%s, flag:%d\n", str, flag);
		if (str[1] && !flag && is_target(set, str[0]) && \
			!is_target(set, str[1])) // if !flag && str[0] == spaces, str[1] !spaces
			wc++;
		if (!flag && str[0] && is_target("'\"", str[0]))
			symbol = str[0];
		if (!flag && str[0] == symbol && str[0 - 1])
			flag = 1;
		else if (flag && str[0] == symbol)
			flag = 0;
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
	if (str)
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
int	count_chr(char *str, char *set, int *flag)
{
	int		count;
	char	symbol;

	/* var='90 > 90' */
	/* cmd1 cmd2 */
	/* '90 > 90'= var */

	// /*debug*/printf("count_chr_str entry:%s\n", str);
	count = 0;
	symbol = '\0';
	while (str[0] && (!is_target(set, str[0]) || (*flag == 1)))
	{
		if (*flag == 0 && str[0] && is_target("'\'\"", str[0])) // if is first encounter to '
			symbol = str[0];
		if (*flag == 0 && str[0] == symbol) // if is first encounter to '
			*flag = increment_val(1, &count, &str); // increment & set flag to 1
		else if (*flag == 1 && str[0] == symbol)
			*flag = 0;
		if (*flag)
			increment_val(-1, &count, &str);
		else if (!*flag && !is_target(set, str[0]))
			increment_val(-1, &count, &str);
		/* if flag == 1, ignore sets */
		/* if flag != 1, stop upon sets */
	}
	// /*debug*/printf("flag:%d, stopped:%s, %d\n", *flag, str, count);
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
	int		count;

	if (!str || !set)
		return (NULL);
	i = 0;
	f = 0;
	str = skip_spaces(str, set);
	res = (char **)malloc(sizeof(char *) * (count_str(str, set) + 1));
	/*debug*/printf("\033[102mcount_str= %d+1\033[0m\n", count_str(str, set));
	while (str[0] && count_str(str, set))
	{
		// /*debug*/printf("split_enter:%s\n", str);
		x = 0;
		f = 0;
		count = count_chr(str, set, &f);
		res[i] = (char *)malloc(sizeof(char) * (count + 1));
		while (x < count)
			res[i][x++] = *str++;
		res[i][x] = '\0';
		// /*debug*/printf("\033[103msplit_stopped:%s\033[0m\n", str);
		i++;
		str = skip_spaces(str, set);
	}
	res[i] = NULL;
	return (res);
}
