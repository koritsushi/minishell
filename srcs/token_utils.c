/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:18:26 by hsim              #+#    #+#             */
/*   Updated: 2025/03/02 08:59:45 by hsim             ###   ########.fr       */
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

/* skips if str[0] == *set */
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
	if (c == symbol)
	{
		str = ft_strchr(str, ' ');
		str = skip_spaces(str, " \t\n\v\f\r");
	}
	return (str);
}

/* splits current *str by *set and see if there are strings after splitting */
int	has_more_str(char *str, char *set)
{
	char	**check;
	int		res;

	res = 0;
	check = ft_split_shell(str, set);
	if (check && check[1])
		res = 1;
	free_chr_ptr((void **)check);
	return (res);
}

/*
 * checks all pointer array **str by *set 
 * and see if there are strings after splitting
 */
int	has_more_str_all(char **str, char *set)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (has_more_str(str[i], set))
			return (1);
		i++;
	}
	return (0);
}

