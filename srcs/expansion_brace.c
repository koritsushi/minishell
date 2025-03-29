/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_brace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:29:13 by hsim              #+#    #+#             */
/*   Updated: 2025/03/29 22:59:36 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	/* check for {a{a,b} */
	flag = 0;
	while (str && str[0])
	{
		if (str[0] && is_target(" \t\n\v\f\r{", str[0]))
			break ;
		else if (str[0] == ',')
			flag = 1;
		else if (str[0] == '}' && flag)
		{
			/*debug*/printf("is_valid_brace_start:%s.\n", str);
			return (1);
		}
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
static char	*get_brace_outer(char *str, char symbol)
{
	int		len;
	char	*new;

	if (!str)
		return (str);
	len = 0;
	while ((str[len] == symbol && str[len + 1] == symbol) || \
		str[len] != symbol)
		len++;
	if (!malloc_chr_ptr(&new, len + 1))
		return (0);
	len = 0;
	while (str[0] != symbol || (str[0] == symbol && str[1] == symbol))
		new[len++] = *str++;
	new[len] = '\0';
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

/*
 * expands brace part accordingly
 * int x = the index number to copy to in *dest
 */
char	*copy_brace_expansion(char *src, char *dest, int *x, int malloc_size)
{
	int		flag;
	char	*head;
	char	*tail;

	/*debug*/printf("copy_brace_expansion:ent:\033[93m%s\033[0m.\n", src);
	/*debug*/printf("copy_brace_expansion:dest:\033[93m%s\033[0m.x=%d\n", &dest[*x], *x);
	flag = 0;
	// head = get_brace_outer(src, '{');
	head = get_brace_head(src);
	/* src need to move to valid_brace_start */
	while (!is_valid_brace_start(src))
		src++;
	// src = ft_strchr(src, '{');
	// while (src[0] == '{')
		// src++;
	tail = get_brace_outer(ft_strchr(src, '}') + 1, ' ');
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
		// /*debug*/printf("brace_body:\033[93m%c\033[0m%s.\n", src[0], src + 1);
		dest[(*x)] = '\0'; //can remove
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

/*
 * child function in brace_expansion
 * expand and replace the cmd_line by freeing & re-malloc
 */
void	perform_brace_expansion(char **cmd_line, int malloc_size)
{
	int		len;
	int		x;
	char	*str;
	char	*new;
	/* calculate new malloc string */
	/* front a{,}e back */
	/* front a{r,o}e back */
	/* are aoe */
	/* a{,}e=5-2=3, 3+ 2x1=2, 3+2=5 */
	/* front a{b,c,d}e back */
	/* 9-2=7, 2*2=4, 7+4=11 */
	/* 9, +2 */
	/* front abe ace ade back*/
	/* 7, 2*2=4, 7+4=11 */

	x = 0;
	len = 0;
	str = *cmd_line;
	malloc_chr_ptr(&new, malloc_size + 1);
	while (str && str[0] && x < malloc_size)
	{
		if (str[0] && is_target(" \t\n\v\f\r", str[0]))
			len = -1;
		if (str[0] == '{' && str[1] != '{')
		{
			/*debug*/printf("x=%d len=%d %c\n", x, len, str[0]);
			x -= len;
			copy_brace_expansion(str - len, new, &x, malloc_size);
			str = ft_strchr(str, ' ');
			/*debug*/printf("str:%s.\n", str);
		}
		else
			new[x++] = *str++;
		len++;
	}
	free(*cmd_line);
	*cmd_line = new;
	/*debug*/printf("perform_brace_expansion:res:\033[93m%s\033[0m. x:%d\n", new, x);
	// /*debug*/printf("perform_brace_expansion:res:\033[93m%s\033[0m. x:%d\n", *cmd_line, x);
}
