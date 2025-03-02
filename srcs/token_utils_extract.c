/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_extract.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:06:36 by hsim              #+#    #+#             */
/*   Updated: 2025/03/02 18:27:50 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

// 16 lines!
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

    /*debug*/
	// printf("------\ninfile:\n");
	// debug_print(infile);
	// printf("------\nINFILE=%s\n", *lst_data);
    /*debug_end*/

	free_chr_ptr((void **)infile_fin);
}

/* get & saves outfile string into lst_data */
void	extract_outfile(char **lst_data, char *str)
{
	int		i;
	char	**outfile_fin;

	i = 0;
	outfile_fin = ft_split_shell(str, " \t\n\v\f\r");
	allocate_str(lst_data, outfile_fin[0]);
	ft_strlcpy(*lst_data, outfile_fin[0], ft_strlen(outfile_fin[0]) + 1);

	// /*debug*/ printf("------\noutfile_fin:\n");
	// /*debug*/ debug_print(outfile_fin);

	free_chr_ptr((void **)outfile_fin);
}

/* child function in process_cmd_tail, *i = lst_data index number */
void	process_outfile(char **lst_data, int *i, char *cmd_tail, char **outfile)
{
	int	k;

	k = 1;
	/* if start with '>' */
	if (cmd_tail[0] == '>')
		extract_outfile(&lst_data[(*i)++], outfile[0]);
	/* if not start with '>' */
	while (outfile[k])
		extract_outfile(&lst_data[(*i)++], outfile[k++]);
}
