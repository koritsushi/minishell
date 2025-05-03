/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_brace_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:54:34 by hsim              #+#    #+#             */
/*   Updated: 2025/05/03 08:28:34 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *   utils function to get content of brace_head & brace_tail,
 *   then copy to dest
 * ************************************************************************** */

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
	// /*debug*/printf("has_valid_brace_content:ent:%s\n", str);
	/* increment until is_valid_brace_start */
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
	// /*debug*/printf("has_valid_brace_content:end:%s. flag:%d\n", str, flag);
	return (flag);
}

/*
 * child function in copy_brace_expansion
 * moves char* pointer to where the valid brace start is {,}
 */
static char	*move_to_valid_brace_start(char *src)
{
	while (src && !is_valid_brace_start(src))
	{
		if (src[0] && is_target("\'\"", src[0]) && \
skip_if_quote(src, src[0], 0))
			src = skip_if_quote(src, src[0], 0) + 1;
		else
			src++;
	}
	return (src);
}

// 20 lines!
/*
 * child function in copy_brace_expansion
 * gets expansion content outside of brace: 
 * eg a{,}z, content= a or z
 * mallocs & return the content in a new string
 */
static char	*get_brace_tail(char *str, char *set)
{
	int		x;
	int		len;
	char	*new;

	/*debug*/printf("get_brace_tail:ent:%s\n", str);
	if (!str)
		return (str);
	len = 0;
	while (str[len] && !is_target(set, str[len]))
	{
		/*debug*/printf("get_brace_tail:char:%c\n", str[len]);
		if (is_target("\'\"", str[len]))
		{
			len += skip_if_quote(&str[len], str[len], 0) - &str[len] + 1;
			// /*debug*/printf("get_brace_tail:quote:%d\n", res);
		}
		else
			len++;
	}
	/*debug*/printf("get_brace_tail:malloc:%d+1\n", len);
	if (!malloc_chr_ptr(&new, len + 1))
		return (0);
	x = 0;
	while (str[0] && x < len)
		new[x++] = *str++;
	return (new);
}

// 20 lines!
/*
 * child function in copy_brace_expansion
 * gets expansion content outside of brace: 
 * eg a{,}z, content= a or z
 * mallocs & return the content in a new string
 */
static char	*get_brace_head(char *str)
{
	char	*new;
	int		len;
	int		x;

	if (!str)
		return (str);
	len = 0;
	// flag_quote = 0;
	// symbol = '\0';
	/* {a{a,e}e*/
	/* a{a,e}e */ //previous
	/* "a p"{a,e}e*/ //future
	while (str[len] && (!is_valid_brace_start(&str[len] + 1)))
	{
		if (is_target("\'\"", str[len]))
			len += ft_strchr(&str[len + 1], str[len]) - &str[len] + 1;
		else
			len++;
		/* can use ft_strchr instead and len += */
		/* len += ft_strchr() - &str[len] */
		// update_flag_quote(str[len], &symbol, &flag_quote);
	}
	/*debug*/printf("get_brace_head:str:%s. len:%d+1\n", str, len);
	if (!malloc_chr_ptr(&new, len + 1))
		return (0);
	x = 0;
	while (str[0] && x < len)
		new[x++] = *str++;
	return (new);
}

// 24 lines!
/*
 * expands brace part accordingly
 * (copy head, copy content in brace, copy tail, repeat)
 * int x = the index number to copy to in *dest
 */
char	*copy_brace_expansion(char *src, char *dest, int *x, int malloc_size)
{
	int		flag;
	char	*head;
	char	*tail;

	/*debug*/printf("copy_brace_expansion:ent:\033[93m%s\033[0m.\n", src);
	flag = 0;
	head = get_brace_head(src);
	src = move_to_valid_brace_start(src);
	tail = get_brace_tail(ft_strchr(src, '}') + 1, " \t\n\v\f\r");
	/*debug*/printf("src=%s.\nget_brace_head:\033[93m%s\033[0m.\nget_brace_tail:\033[93m%s\033[0m.\n", src, head, tail);
	while (src && src[0] && *x < malloc_size)
	{
		if (flag)
			dest[(*x)++] = ' ';
		else if (!flag)
			flag = 1;
		*x += ft_strlcpy(&dest[*x], head, ft_strlen(head) + 1);
		while (src[0] && !is_target(",{}", src[0]))
			dest[(*x)++] = *src++;
		/*debug*/printf("half:\033[93m%s\033[0m, x=%d, src[0]=%c\n", dest, *x, src[0]);
		*x += ft_strlcpy(&dest[*x], tail, ft_strlen(tail) + 1);
		if (src[0] == '}')
		{
			// /*debug*/printf("break!\n");
			break ;
		}
		src++;
	}
	free_multiple_ptr_single(head, tail, NULL);
	// /*debug*/printf("copy_brace_expansion:end:\033[93m%s\033[0m.\n", dest);
	return (dest);
}
