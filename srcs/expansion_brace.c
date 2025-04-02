/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_brace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:29:13 by hsim              #+#    #+#             */
/*   Updated: 2025/04/02 15:07:19 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

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
	int		len;
	int		flag;
	int		flag_quote;
	char	symbol;

	len = 0;
	flag = 0;
	flag_quote = 0;
	symbol = '\0';
	/*count head, count tail*/
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
			// /*debug*/printf("tmp=\033[93m%c\033[0m%s. \033[93mlen=%d\033[0m\n", str[0], str+1, len);
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
	/* 8-2=6, 5x1=5, 11*/

	/*debug*/printf("get_expansion_count:ent:%s.\n", str);
	len = 0;
	comma = 0;
	str = skip_spaces(str, " \t\n\v\f\r");
	comma = count_brace_comma(str);
	len = count_brace_content(str);
	/*debug*/printf("comma=%d len=%d\n", comma, len);
	return (len * comma);

}

/*
 * child function in start_brace_operation
 * skips entire valid_brace and point to the first space ' ' after brace end
 */
static char	*skip_braces(char *str)
{
	if (!str)
		return (str);
	// /*debug*/printf("skip_braces:ent:%s.\n", str);
	while (str[0] && !is_target(" \t\n\v\f\r", str[0]))
	{
		if (is_target("\'\"", str[0]) && ft_strchr(str + 1, str[0]))
			str = ft_strchr(str + 1, str[0]) + 1;
		else
			str++;
	}
	// /*debug*/printf("skip_braces:end:%s.\n", str);
	return (str);
}

// 22 lines!
/*
 * child function in perform_brace_expansion
 * copy, expands, and point to next available spaces ' ' when done
 */
static void	start_brace_operation(char *src, char *dest, int malloc_size)
{
	int		x;
	int		len;
	int		flag;
	int		flag_quote;
	char	symbol;

	x = 0;
	len = 0;
	flag = 0;
	flag_quote = 0;
	symbol = '\0';
	while (src && src[0] && x < malloc_size)
	{
		update_flag_quote(src, &symbol, &flag_quote);
		if (src[0] && is_target(" \t\n\v\f\r", src[0]) && !flag_quote)
			len = -1;
		if (src[0] == '{' && is_valid_brace_start(src + 1) && !flag)
		{
			/* "ar e"{,}v */
			/*debug*/printf("x=%d len=%d %c\n", x, len, src[0]);
			x -= len;
			copy_brace_expansion(src - len, dest, &x, malloc_size);
			//forsee bugs here when:  "ar e"{,"so m"}v
			// src = ft_strchr(src, ' '); 
			src = skip_braces(src);
			flag = 1;
			/*debug*/printf("str:%s.\n", src);
		}
		else
			dest[x++] = *src++;
		len++;
	}
	/*debug*/printf("perform_brace_expansion:res:\033[93m%s\033[0m. x:%d\n", dest, x);
}

/*
 * child function in brace_expansion
 * copies over head content up to beginning of valid_brace (a{,}e)
 * expand + replace the cmd_line by freeing & re-malloc
 */
void	perform_brace_expansion(char **cmd_line, char *str, int malloc_size)
{
	char	*dest;
	int		x;
	/* calculate new malloc string */
	/* front a{b,c,d}e back */
	/* front abe ace ade back*/
	/* 7, 2*2=4, 7+4=11 */
	// /*debug*/printf("perform_brace_expansion:ent:%s.\n", str);
	malloc_chr_ptr(&dest, malloc_size + 1);
	x = -1;
	while (str - &(*cmd_line)[++x] > 0)
		dest[x] = (*cmd_line)[x];
	// /*debug*/printf("perform_brace_expansion:diff:%ld, %s\n", str - &(*cmd_line)[x], &(*cmd_line)[x]);
	start_brace_operation(str, &dest[x], malloc_size);
	free(*cmd_line);
	*cmd_line = dest;
}
