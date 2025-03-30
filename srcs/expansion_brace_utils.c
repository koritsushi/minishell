/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_brace_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:54:34 by hsim              #+#    #+#             */
/*   Updated: 2025/03/30 09:08:23 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

/* utils function to count expansion content for malloc use */

/*
 * child function in get_expansion_count
 * counts valid comma within brace {,} only for the 1st brace occurence
 * eg. {,}a{,}b : comma = 1 (only count comma in the 1st brace)
 */
static int	count_brace_comma(char *str)
{
	int	comma;

	comma = 0;
	while (!is_valid_brace_start(str))
		str++;
	while (str && str[0] && str[0] != '}')
	{
		if (str[0] == ',')
			comma++;
		str++;
	}
	return (comma);
}

/*
 * child function in get_expansion_count
 * counts char that it outside of brace {,} (1st brace occurence)
 * eg. {,}a{,}b :  len=5 (a{,}b)
 */
static int	count_brace_content(char *str)
{
	int	len;
	int	flag;

	len = 0;
	flag = 0;
	while (str && str[0] && !is_target(" \t\n\v\f\r", str[0]))
	{
		/* identify if its the correct brace set , if true, strchr it*/
		if (str[1] && str[0] == '{' && is_valid_brace_start(str + 1) && !flag)
		{
			str = ft_strchr(str, '}');
			flag = 1;
		}
		else
		{
			// /*debug*/printf("tmp=\033[93m%c\033[0m%s. \033[93mlen=%d\033[0m\n", str[0], str+1, len);
			/*debug*/printf("tmp=\033[93m%c\033[0m%s.\n", str[0], str+1);
			len++;
		}
		if (str)
			str++;
	}
	return (len);
}

// 24 lines!
/* counts the brace_expansion area when fully expanded */
int	get_expansion_count(char *str)
{
	int		len;
	int		flag;
	int		comma;

	/* 6-2=4 */
	/* a{,}e */
	/* 5-2=3 2x1=2 ==5 */
	/* a{,}e{ */
	/* 6-2=4 3x1=3 ==7 */
	/* {,}a{,}b */
	/* 8-2=6, 5x1=5, 11*/

	// /*debug*/printf("get_expansion_count:ent:%s.\n", str);
	len = 0;
	flag = 0;
	comma = 0;
	str = skip_spaces(str, " \t\n\v\f\r");
	comma = count_brace_comma(str);
	len = count_brace_content(str);
	/*debug*/printf("comma=%d len=%d\n", comma, len);
	return (len * comma);

}