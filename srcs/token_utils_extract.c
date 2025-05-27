/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_extract.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:06:36 by hsim              #+#    #+#             */
/*   Updated: 2025/05/27 16:00:47 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/*
 * child function of extract_infile
 * mallocs enough space & copy corresponding infile
 * uses malloc
 */
static void	alloc_copy_infile(char **infile, char **lst_data, int *i)
{
	int		x;
	char	**fin;
	char	**infile_fin;

	x = 0;
	infile_fin = ft_split_shell(infile[x], ">");
	fin = ft_split_shell(infile_fin[0], " \t\n\v\f\r");
	allocate_str(&lst_data[(*i)], fin[0]);
	ft_strlcpy(lst_data[(*i)++], fin[0], ft_strlen(fin[0]) + 1);
	free_multiple_ptr(infile_fin, fin, NULL);
}

// 16 lines!
/*
 * child function of extract_cmd
 * jump to where 1st infile occur, split by spaces & malloc+copy
 * uses malloc
 */
void	extract_infile(char **lst_data, int *i, char *res)
{
	int		x;
	char	**infile;

	x = -1;
	//extract all infiles
	/*get to the last infile index*/
	infile = ft_split_shell(res, "<");
	if (res[0] != '<')
		x++;
	// <in1 in2 <in3 cmd | <in3 cmd
	// cmd -k <in1 <in2 in3 | <in3 cmd
	// jump to where 1st infile occur
	// split
	while (infile[++x])
		alloc_copy_infile(&infile[x], lst_data, i);
	free_chr_ptr((void **)infile);
}

/* get & saves outfile string into lst_data */
void	extract_outfile(char **lst_data, char *str)
{
	char	**outfile_fin;

	outfile_fin = ft_split_shell(str, " \t\n\v\f\r");
	allocate_str(lst_data, outfile_fin[0]);
	ft_strlcpy(*lst_data, outfile_fin[0], ft_strlen(outfile_fin[0]) + 1);
	// /*debug*/ printf("------\noutfile_fin:\n");
	// /*debug*/ debug_print(outfile_fin);

	free_chr_ptr((void **)outfile_fin);
}

/* child function in process_cmd_tail, *i = lst_data index number */
void	process_outfile(char **lst_data, int *i, char *cmd_tail)//, char **outfile)
{
	int		k;
	char	*tmp;
	char	**outfile;

	outfile = ft_split_shell(cmd_tail, ">");
	if (!outfile || !outfile[0])
		return ;
	// /*debug*/printf("process_outfile:ent:%s.\n", cmd_tail);
	k = 1;
	if (cmd_tail[0] != '>' && skip_consecutive_redir(outfile[0], 0))
		tmp = skip_consecutive_redir(outfile[0], 0);
	else
		tmp = outfile[0];
	// /*debug*/printf("process_outfile:%s.\n", tmp);
	if (cmd_tail[0] == '>')
		extract_outfile(&lst_data[(*i)++], tmp);
	while (outfile[k])
		extract_outfile(&lst_data[(*i)++], outfile[k++]);
	free_chr_ptr((void **)outfile);
}
