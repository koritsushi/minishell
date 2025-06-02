/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_brace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:29:13 by hsim              #+#    #+#             */
/*   Updated: 2025/05/29 18:36:53 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

/*
 * child function in expand_brace_content
 * skips entire valid_brace and point to the first space ' ' after brace end
 */
static char	*skip_braces(char *str)
{
	if (!str)
		return (str);
	while (str[0] && !is_target(" \t\n\v\f\r", str[0]))
	{
		if (is_target("\'\"", str[0]) && ft_strchr(str + 1, str[0]))
			str = ft_strchr(str + 1, str[0]) + 1;
		else
			str++;
	}
	return (str);
}

/*
 * child function in expand_brace_content
 * expand brace and copy all the remainder til end
 * returns src pointing to '\0' when done
 * src = src-len,  x = x-len
 */
static char	*copy_til_brace_end(char *src, char *dest, int x, int malloc_size)
{
	{
		copy_brace_expansion(src, dest, &x, malloc_size);
		src = skip_braces(src);
		while (src && src[0] && x < malloc_size)
			dest[x++] = *src++;
		return (src);
	}
}

/*
 * child function in start_brace_expansion
 * copy, expands, and point to next available spaces ' ' when done
 */
static void	expand_brace_content(char *src, char *dest, int malloc_size)
{
	int		x;
	int		len;
	int		flag_quote;
	char	symbol;

	x = 0;
	len = 0;
	flag_quote = 0;
	symbol = '\0';
	while (src && src[0] && x < malloc_size)
	{
		update_flag_quote(src, &symbol, "\'\"", &flag_quote);
		if (src[0] && is_target(" \t\n\v\f\r", src[0]) && !flag_quote)
			len = -1;
		if (src[0] == '{' && is_valid_brace_start(src + 1))
			src = copy_til_brace_end(src - len, dest, x - len, malloc_size);
		else
			dest[x++] = *src++;
		len++;
	}
}

/*
 * child function in perform_brace_expansion
 * copies over head content up to beginning of valid_brace (a{,}e)
 * expand + replace the cmd_line by freeing & re-malloc
 */
static void	start_brace_expansion(char **cmd_line, char *str, int malloc_size)
{
	char	*dest;
	int		x;

	malloc_chr_ptr(&dest, malloc_size + 1);
	x = -1;
	while (str - &(*cmd_line)[++x] > 0)
		dest[x] = (*cmd_line)[x];
	expand_brace_content(str, &dest[x], malloc_size);
	free(*cmd_line);
	*cmd_line = dest;
}

/*
 * child function in brace_expansion
 * counts malloc size & expands brace
 * cmd_line = the full original line, need to copy from and remalloc free it
 */
char	*perform_brace_expansion(char *str, char **cmd_line, int *x)
{
	int	len;

	len = 0;
	len = ft_strlen(*cmd_line) - 2 + get_expansion_count(str - (*x));
	start_brace_expansion(cmd_line, str - (*x), len);
	*x = -1;
	return (*cmd_line);
}
