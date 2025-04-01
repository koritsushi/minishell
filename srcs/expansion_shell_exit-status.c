/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_shell_exit-status.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:40:41 by hsim              #+#    #+#             */
/*   Updated: 2025/04/01 11:48:52 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

static char	*start_exit_expansion(char *src, char *dest, char *exit_code, int len)
{
	int	x;

	x = 0;
	while (src && src[0] && x < len)
	{
		/*debug*/printf("expand_exit_status:%s\n", src);
		if (src[0] == '$' && src[1] && src[1] == '?')
		{
			x += ft_strlcpy(&dest[x], exit_code, \
						ft_strlen(exit_code) + 1);
			src += 2;
		}
		else
			dest[x++] = *src++;
	}
	return (dest);
}

// 25 lines!
/*
 * child function in shell_var_expansion
 * expand '$?' to exit_status code,
 * replace cmd_line with the expanded content
 * uses malloc
 */
char	*expand_exit_status(char **cmd_line, int exit_status)
{
	int		len;
	char	*new;
	char	*exit_code;

	exit_code = ft_itoa(exit_status);
	len = ft_strlen(*cmd_line) - 2;
	len += ft_strlen(exit_code);
	/*debug*/printf("expand_exit_status:malloc_len:%d+1\n", len);
	if (!malloc_chr_ptr(&new, len + 1))
		return (0);
	start_exit_expansion(*cmd_line, new, exit_code, len);
	free_multiple_ptr_single(2, *cmd_line, exit_code);
	*cmd_line = new;
	return (*cmd_line);
}
