/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_brace_utils_count.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:41:58 by hsim              #+#    #+#             */
/*   Updated: 2025/05/31 18:28:15 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   helper function to count malloc needed for brace_expansions
 * ************************************************************************** */

#include "includes/expansion.h"

/*
 * checks if flag_quote is on, update status accordingly
 * target = str[0], symbol = &symbol, flag_quote = &flag_quote
 * set = a set of chars that'll raise the flag
 */
void	update_flag_quote(char *target, char *set, char *symbol, \
int *flag_quote)
{
	if (!target)
		return ;
	if (!(*flag_quote) && is_target(set, target[0]))
	{
		*flag_quote = 1;
		*symbol = target[0];
	}
	else if (*flag_quote && target[0] == *symbol)
		*flag_quote = 0;
}

/*
 * child funcion in get_expansion_count
 * checks if the current str[0] is start of a valid brace structure
 * which consists exactly {,} (eg {a,b})
 * ideally when enter str[0] == '{' , input str+1
 */
int	is_valid_brace_start(char *str)
{
	int		flag;
	int		flag_quote;
	char	symbol;

	flag = 0;
	flag_quote = 0;
	symbol = '\0';
	while (str && str[0])
	{
		update_flag_quote(str, "\'\"", &symbol, &flag_quote);
		if (str[0] && is_target(" \t\n\v\f\r{", str[0]) && !flag_quote)
			break ;
		else if (str[0] == ',')
			flag = 1;
		else if (str[0] == '}' && flag)
			return (1);
		str++;
	}
	return (0);
}

/*
 * child function in get_expansion_count
 * counts valid comma within brace {,} only for the 1st brace occurence
 * eg. {,}a{,}b : comma = 1 (only count comma in the 1st brace)
 */
static int	count_brace_comma(char *str)
{
	int	comma;

	comma = 0;
	while (str[0])
	{
		if (str[0] == '{' && is_valid_brace_start(str + 1))
			break ;
		str++;
	}
	while (str && str[0] && str[0] != '}')
	{
		if (str[0] && is_target("\'\"", str[0]))
			str = skip_if_quote(str, str[0], 0);
		else if (str[0] == ',')
			comma++;
		str++;
	}
	return (comma);
}

/*
 * child function in get_expansion_count
 * counts char that is outside of brace {,} (brace head & tail, only 1st brace)
 * eg. {,}a{,}b :  len=5 (a{,}b)
 */
static int	count_brace_content(char *str)
{
	int		len;
	int		flag;
	int		flag_quote;
	char	symbol;

	len = 0;
	flag = 0;
	symbol = '\0';
	flag_quote = 0;
	while (str && str[0] && (!is_target(" \t\n\v\f\r", str[0]) || flag_quote))
	{
		update_flag_quote(str, "\'\"", &symbol, &flag_quote);
		if (str[1] && str[0] == '{' && is_valid_brace_start(str + 1) && !flag)
		{
			str = ft_strchr(str, '}');
			flag = 1;
		}
		else
			len++;
		if (str)
			str++;
	}
	return (len);
}

/* counts the brace_expansion area when fully expanded */
int	get_expansion_count(char *str)
{
	int		len;
	int		comma;

	len = 0;
	comma = 0;
	str = skip_spaces(str, " \t\n\v\f\r");
	comma = count_brace_comma(str);
	len = count_brace_content(str);
	return (len * comma);
}
