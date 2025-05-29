/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_shell_exit-status.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:40:41 by hsim              #+#    #+#             */
/*   Updated: 2025/05/29 14:31:29 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

void	dot_expansion(char **cmd_line)
{
	int		x;
	char	*str;
	char	*new;

	x = 0;
	str = *cmd_line;
	if (ft_strncmp(str, "../", 3) == 0)
		return ;
	else if (ft_strncmp(str, "./", 2) == 0)
	{
		if (str[x + 2])
		{
			malloc_chr_ptr(&new, ft_strlen(*cmd_line));
			ft_strlcpy(new, *cmd_line, x + 1);
			ft_strlcpy(&new[x], &str[x + 1], ft_strlen(&str[x + 1]) + 1);
			free(*cmd_line);
			*cmd_line = new;
		}
	}
}

// 25 lines!
/*
 * child function in shell_var_expansion
 * expand '$?' to exit_status code,
 * replace cmd_line with the expanded content
 * updates int to the index after expansion
 * uses malloc
 */
char	*expand_exit_status(char **cmd_line, int exit_status, int *index)
{
	int		len;
	char	*new;
	char	*exit_code;

	exit_code = ft_itoa(exit_status);
	len = ft_strlen(*cmd_line) - 2;
	len += ft_strlen(exit_code);
	// /*debug*/printf("expand_exit_status:malloc_len:%d+1\n", len);
	if (!malloc_chr_ptr(&new, len + 1))
		return (0);
	// /*debug*/printf("expand_exit_status:ent:%s.\n", *cmd_line);
	// /*debug*/printf("expand_exit_status:str:%s. %d\n", &(*cmd_line)[*index], *index);
	// /*debug*/printf("expand_exit_status:index:%lu\n", (*index) + ft_strlen(exit_code));
	ft_strlcpy(new, *cmd_line, *index + 1);
	ft_strlcpy(&new[(*index)], exit_code, ft_strlen(exit_code) + 1);
	ft_strlcpy(&new[(*index) + ft_strlen(exit_code)], \
&(*cmd_line)[(*index) + 2], ft_strlen(&(*cmd_line)[(*index) + 2]) + 1);

	// /*debug*/printf("expand_exit_status:new:%s.\n", new);

	*index += ft_strlen(exit_code);
	free_multiple_ptr_single(*cmd_line, exit_code, NULL);
	*cmd_line = new;
	return (*cmd_line);
}
