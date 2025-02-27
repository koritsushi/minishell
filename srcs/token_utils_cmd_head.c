/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_cmd_head.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:18:26 by hsim              #+#    #+#             */
/*   Updated: 2025/02/27 07:24:26 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/*
 * child function of extract_cmd
 * int start = index position of where to copy over the text
 * uses malloc
 */
void	extract_infile(char **lst_data, char **res, char **infile)
{
	int		i;
	char	**infile_fin;

	i = 0;
	/*get to the last infile index*/
	while (infile && infile[i + 1])
		i++;
	infile_fin = ft_split_shell(infile[i], " \t\n\v\f\r");

	i = 0;
	if (res[0][0] != '<' && infile[1])
	{
		while (infile_fin[i + 1] && infile_fin[i + 1][0] != '>')
			i++;
	}
	allocate_str(lst_data, infile_fin[i]);
	ft_strlcpy(*lst_data, infile_fin[i], ft_strlen(infile_fin[i]) + 1);

	printf("------\ninfile:\n");
	debug_print(infile);
	printf("------\nINFILE=%s\n", *lst_data);

	free_chr_ptr((void **)infile_fin);
}

char	*skip_spaces(char *str, char *set)
{
	char	*tmp;

	tmp = str;
	while (tmp && tmp[0] && is_target(set, tmp[0]))
		tmp++;
	return (tmp);
}

/* 
 * child function for extract_cmd_head & process_cmd_tail
 * *str = the string to check/iterate
 * skips if str[0] == *set
 * if char c == symbol, skips *str to the 1st occurence of spaces
 */
char	*skip_if_symbol(char *str, char c, char symbol)
{
	// while (str[0] && is_target(set, str[0]))
		// str++;
	if (c == symbol)
	{
		str = ft_strchr(str, ' ');
		str = skip_spaces(str, " \t\n\v\f\r");
		// while (str[0] && is_target(" \t\n\v\f\r", str[0]))
			// str++;
	}
	return (str);
}

/* extracts command properly skipping the infiles */
/* can update **res to *str (follow extract_cmd_tail)*/
void	extract_cmd_head(char **lst_data, char **res, char **infile)
{
	char	*cmd_head;
	char	**cmd_head_fin;

	cmd_head = infile[0];
	// while (is_target(" \t\n\v\f\r", cmd_head[0]))
		// cmd_head++;
	cmd_head = skip_spaces(cmd_head, " \t\n\v\f\r");
	cmd_head = skip_if_symbol(cmd_head, res[0][0], '<');
	cmd_head_fin = ft_split_shell(cmd_head, ">");
	allocate_str(lst_data, cmd_head_fin[0]);
	ft_strlcpy(*lst_data, cmd_head_fin[0], ft_strlen(cmd_head_fin[0]) + 1);
	free_chr_ptr((void **)cmd_head_fin);
}
