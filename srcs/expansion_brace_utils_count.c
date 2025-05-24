/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_brace_utils_count.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:41:58 by hsim              #+#    #+#             */
/*   Updated: 2025/05/24 16:32:08 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   helper function to count malloc needed for brace_expansions
 * ************************************************************************** */

#include "includes/expansion.h"

/*
 * checks if flag_quote is on, update status accordingly
 * target = str[0], symbol = &symbol, flag_quote = &flag_quote
 */
void	update_flag_quote(char *target, char *symbol, int *flag_quote)
{
	// /*debug*/printf("update_flag_quote:%c\n", target[0]);
	if (!(*flag_quote) && is_target("\'\"", target[0]))
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

	/* "a rt"{,}e're w' */
	flag = 0;
	flag_quote = 0;
	symbol = '\0';
	/*debug*/printf("is_valid_brace_start:ent:%s, %c\n", str, str[0]);
	while (str && str[0])
	{
		update_flag_quote(str, &symbol, &flag_quote);
		// /*debug*/printf("is_valid_brace_start:%c. flag_q:%d\n", str[0], flag_quote);
		if (str[0] && is_target(" \t\n\v\f\r{", str[0]) && !flag_quote)
			break ;
		else if (str[0] == ',')
			flag = 1;
		else if (str[0] == '}' && flag)
			return (1);
		str++;
	}
	/*debug*/printf("\033[93mnot valid_brace_start!\033[0m\n");
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
	// 'v'{,}e
	/*debug*/printf("count_brace_comma:ent:%s.\n", str);
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

// 23 lines!
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
		/*debug*/printf("\033[100mcount_brace_content:ent:%s\033[0m\n", str);
		update_flag_quote(str, &symbol, &flag_quote);
		/* identify if its the correct brace set , if true, strchr it*/
		/*debug*/printf("count_brace_content!\n");
		if (str[1] && str[0] == '{' && is_valid_brace_start(str + 1) && !flag)
		{
			str = ft_strchr(str, '}');
			flag = 1;
		}
		else
		{
			/*debug*/printf("tmp=\033[93m%c\033[0m%s.\n", str[0], str+1);
			len++;
		}
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

	/* 6-2=4 */
	/* a{,}e */
	/* 5-2=3 2x1=2 ==5 */
	/* aa{b,c}ee */
	/* 9-2=7 4x1=4 ==11 */
	/* a{,}e{ */
	/* 6-2=4 3x1=3 ==7 */
	/* {,}a{,}b */
	/* 8-2=6, 5x1=5, 11 */

	/*debug*/printf("get_expansion_count:ent:%s.\n", str);
	len = 0;
	comma = 0;
	str = skip_spaces(str, " \t\n\v\f\r");
	comma = count_brace_comma(str);
	len = count_brace_content(str);
	/*debug*/printf("comma=%d len=%d\n", comma, len);
	return (len * comma);

}
