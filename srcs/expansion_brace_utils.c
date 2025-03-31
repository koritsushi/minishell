/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_brace_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:54:34 by hsim              #+#    #+#             */
/*   Updated: 2025/03/31 09:28:01 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

/* 
 * utils function to get content of brace_head & brace_tail,
 * then copy to dest
 * ************************************************************************** */

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
	while (str[0] && str[0] != '}')
	{
		if (str[0] && is_target(" \t", str[0]))
			return (0);
		else if (str[0] == ',')
			flag = 1;
		str++;
	}
	if (str[0] != '}' && flag)
		return (0);
	return (flag);
}

/*
 * child funcion in get_expansion_count
 * checks if the current str[0] is start of a valid brace structure (eg {a,b})
 */
int	is_valid_brace_start(char *str)
{
	int	flag;

	flag = 0;
	while (str && str[0])
	{
		if (str[0] && is_target(" \t\n\v\f\r{", str[0]))
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
 * child function in copy_brace_expansion
 * gets expansion content outside of brace: 
 * eg a{,}z, content= a or z
 * mallocs & return the content in a new string
 */
static char	*get_brace_tail(char *str, char symbol)
{
	int		x;
	int		len;
	char	*new;

	/*debug*/printf("get_brace_tail:ent:%s\n", str);
	if (!str)
		return (str);
	len = 0;
	while (str[len] && str[len] != symbol) //((str[len] == symbol && str[len + 1] == symbol) ||
		len++;
	/*debug*/printf("get_brace_tail:len:%d\n", len);
	if (!malloc_chr_ptr(&new, len + 1))
		return (0);
	x = 0;
	while (str[0] && x < len && (str[0] != symbol))// || (str[0] == symbol && str[1] == symbol)))
		new[x++] = *str++;
	// new[len] = '\0';
	return (new);
}

/*
 * child function in copy_brace_expansion
 * gets expansion content outside of brace: 
 * eg a{,}z, content= a or z
 * mallocs & return the content in a new string
 */
static char	*get_brace_head(char *str)//, char symbol)
{
	int		len;
	char	*new;

	if (!str)
		return (str);
	len = 0;
	/* {a{a,e}e*/
	while (str[len + 1] && !is_valid_brace_start(&str[len] + 1))// (str[len] == symbol && str[len + 1] == symbol) || str[len] != symbol)
		len++;
	/*debug*/printf("get_brace_head:len:%d+1\n", len);
	if (!malloc_chr_ptr(&new, len + 1))
		return (0);
	len = 0;
	while (str[1] && !is_valid_brace_start(str + 1))//(str[0] != symbol || (str[0] == symbol && str[1] == symbol))
		new[len++] = *str++;
	return (new);
}

// 25 lines!
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
	while (!is_valid_brace_start(src))
		src++;
	tail = get_brace_tail(ft_strchr(src, '}') + 1, ' ');
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
			/*debug*/printf("break!\n");
			break ;
		}
		src++;
	}
	free_multiple_ptr_single(2, head, tail);
	/*debug*/printf("copy_brace_expansion:end:\033[93m%s\033[0m.\n", dest);
	return (dest);
}
