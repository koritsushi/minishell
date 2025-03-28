/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_brace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:29:13 by hsim              #+#    #+#             */
/*   Updated: 2025/03/28 08:28:43 by hsim             ###   ########.fr       */
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
	return (flag);
}

// 24 lines!
/* counts the brace_expansion area when fully expanded */
int	get_expansion_count(char *str)
{
	int		len;
	int		comma;
	char	*tmp;

	/*debug*/printf("get_expansion_count:ent:%s.\n", str);
	tmp = skip_spaces(str, " \t\n\v\f\r");
	comma = 0;
	len = 0;
	while (tmp && tmp[0])
	{
		if (tmp[0] == ',')
			comma++;
		tmp++;
	}
	tmp = skip_spaces(str, " \t\n\v\f\r");
	while (tmp && tmp[0] && !is_target(" \t\n\v\f\r", tmp[0]))
	{
		if (tmp[0] == '{' && tmp[1] != '{')
			tmp = ft_strchr(tmp, '}');
		else
		{
			/*debug*/printf("tmp=%s\n", tmp);
			len++;
		}
		if (tmp)
			tmp++;
	}
	return (len * comma);
}

/*
 * child function in copy_brace_expansion
 * gets expansion content outside of brace: 
 * eg a{,}z, content= a or z
 * uses malloc
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
 * expands brace part accordingly
 * int x = the index number to copy to in *dest
 */
char	*copy_brace_expansion(char *src, char *dest, int *x)
{
	int		flag;
	char	*head;
	char	*tail;

	/*debug*/printf("copy_brace_expansion:ent:\033[93m%s\033[0m.\n", src);
	/*debug*/printf("copy_brace_expansion:dest:\033[93m%s\033[0m.x=%d\n", &dest[*x], *x);
	flag = 0;
	head = get_brace_outer(src, '{');
	tail = get_brace_outer(ft_strchr(src, '}') + 1, ' ');
	src = ft_strrchr(src, '{') + 1;
	/*debug*/printf("get_brace_head:%s.\nget_brace_tail:%s.\n", head, tail);
	while (src && src[0])
	{
		if (flag)
			dest[(*x)++] = ' ';
		else if (!flag)
			flag = 1;
		*x += ft_strlcpy(&dest[*x], head, ft_strlen(head) + 1);
		while (src[0] && !is_target(",{}", src[0]))
			dest[(*x)++] = *src++;
		dest[(*x)] = '\0'; //can remove
		/*debug*/printf("half:%s, x=%d, src[0]=%c\n", dest, *x, src[0]);
		*x += ft_strlcpy(&dest[*x], tail, ft_strlen(tail) + 1);
		if (src[0] == '}')
			break ;
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
	int		flag;
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

	/*calculate_all */
	str = *cmd_line;
	flag = 0;
	x = 0;
	len = 0;
	malloc_chr_ptr(&new, malloc_size + 1);
	while (str && str[0] && !flag && x < malloc_size)
	{
		if (str[0] && is_target(" \t\n\v\f\r", str[0]))
			len = -1;
		if (str[0] == '{' && str[1] != '{')
		{
			/*debug*/printf("x=%d len=%d %c\nnew=%s.\n", x, len, str[0], new);
			x -= len;
			copy_brace_expansion(str - len, new, &x);
			str = ft_strchr(str, ' ');
			/*debug*/printf("str:%s.\n", str);
		// 	flag = 1;
		}
		else
			new[x++] = *str++;
			// new[x++] = str[0];
		// str++;
		len++;
		new[x] = '\0';
	}
	free(*cmd_line);
	*cmd_line = new;
	/*debug*/printf("perform_brace_expansion:res:\033[93m%s\033[0m. x:%d\n", new, x);
	// /*debug*/printf("perform_brace_expansion:res:\033[93m%s\033[0m. x:%d\n", *cmd_line, x);
}
