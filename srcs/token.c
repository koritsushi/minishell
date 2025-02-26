/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:56:04 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/14 19:56:04 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/* get & saves outfile string into lst_data */
void	extract_outfile(char **lst_data, char *str)
{
	int		i;
	char	**outfile_fin;

	// printf("------\noutfile:\n");
	// debug_print(outfile);

	i = 0;
	outfile_fin = ft_split_shell(str, " \t\n\v\f\r");
	allocate_str(lst_data, outfile_fin[0]);
	ft_strlcpy(*lst_data, outfile_fin[0], ft_strlen(outfile_fin[0]) + 1);

	printf("------\noutfile_fin:\n");
	debug_print(outfile_fin);
	// printf("------\nOUTFILE=%s\n", *lst_data);

	free_chr_ptr((void **)outfile_fin);
}

/* 
 * child function of process_cmd_tail
 * allocates enough space to store cmd and copies it
 * str = the entire line of cmd/pipeline before splitted by outfile '>'
 * uses malloc
 */
void	extract_cmd_tail(char **lst_data, char *str, char **outfile)
{
	char	*cmd_tail;
	int		start;
	int		i;

	/* should we skip spaces */
	/* cmd3 > outfile -a -b */
	/* cmd3 > outfile1 > outfile2 -a -b */
	/* > outfile1 > outfile2 -a -b */
	/* > outfile1 > outfile2*/

	/* if (str[0] != '>') */
		/* copy outfile[0] */
		/* skips to the 1st space detected */

	/* if (str[0] == '>') */
		/* skips spaces */
		/* skips to the 1st space detected */

	allocate_cmd_tail(lst_data, outfile, str[0]);
	i = 0;
	start = 0;
	if (str[0] != '>')
	{
		ft_strlcpy(*lst_data, outfile[0], ft_strlen(outfile[0]) + 1);
		start = ft_strlen(outfile[0]);

		i = 1;
	}
	/* if theres outfile*/
	while (outfile[i])
	{
		// cmd_tail = outfile[i];
		/* travel to the first space detected */
		cmd_tail = skip_spaces(outfile[i], " \t\n\v\f\r");
		// while (cmd_tail[0] && is_target(" \t\n\v\f\r", cmd_tail[0]))
			// cmd_tail++;
		cmd_tail = ft_strchr(cmd_tail, ' ');
		cmd_tail = skip_spaces(cmd_tail, " \t\n\v\f\r");
		/*debug*/printf("***cmd_tail=%s| %zu\n", cmd_tail, ft_strlen(cmd_tail));
		if (!cmd_tail)
		{
			printf("!cmd_tail, break!\n");
			break ;
		}
		/* copy to array */
		ft_strlcpy(&(*lst_data)[start], cmd_tail, ft_strlen(cmd_tail) + 1);
		start += ft_strlen(cmd_tail);
		i++;
	}
	/*debug*/printf("tail_fin=%s\n", *lst_data);//, &(*lst_data)[start-3]);
}

/* child function in process_cmd */
void	process_cmd_tail(char **lst_data, char **res)
{
	int		x;
	int		k;
	int		i;
	char	**outfile;
	char	*cmd_tail;

	x = 0;
	i = 0;
	while (res[x])
	{
		cmd_tail = skip_spaces(res[x], "< \t\n\v\f\r");
		cmd_tail = skip_if_symbol(cmd_tail, res[x][0], '<');
		if (!cmd_tail)
			break ;
		outfile = ft_split_shell(cmd_tail, ">");

		/* cmd > outfile1 */
		/* cmd > outfile1 -k */
		/* < infile cmd > outfile */
		/* > outfile1 > outfile2 */
		/* > outfile1 cmd1 > outfile2 -h */

		/* >       outfile1 cmd */
		/* > outfile1 cmd */
		/* cmd */
		/* < infile cmd */

		/*debug*/printf("------\noutfile:\n");
		/*debug*/debug_print(outfile);

		/*--------------extract cmd_tail--------------*/
		/* if splittable && has_more_str_all*/
		if (outfile[1] && (cmd_tail[0] != '>' || \
			(cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))))
			extract_cmd_tail(&lst_data[i++], cmd_tail, outfile);
		/* if not splittable */
		if (!outfile[1])
		{
			/* if begin with >, check if has_more_str_all */
			/* if theres no <>, only single cmd, copy over */
			/* if begin with < (one_line_condition), do not extract */
			if (cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))
				extract_cmd_tail(&lst_data[i++], cmd_tail, outfile);
			if (cmd_tail[0] && !is_target("<>", cmd_tail[0]))
				extract_cmd_tail(&lst_data[i++], cmd_tail, outfile);
		}
		
		/*--------------extract outfiles--------------*/
		/* if start with '>' */
		if (cmd_tail[0] == '>')
			extract_outfile(&lst_data[i++], outfile[0]);
		/* if not start with '>' */
		k = 1;
		while (outfile[k])
			extract_outfile(&lst_data[i++], outfile[k++]);
		x++;
		/*add pipes*/
		if (res[x])
			extract_outfile(&lst_data[i++], "|");
		free_chr_ptr((void **)outfile);
	}

}
/*
 * scans line and saves valid command into a new char** array, str=new
 * uses malloc
 */
void	process_cmd(t_token *lst, char **res, char **infile)// char **outfile)//char *str)
{
	(void)	lst;
	int		i;
	int		x;
	// int		k;
	// char	**outfile;

	/*----------- process_cmd_head || get_infiles -----------*/
	i = 0;
	x = 0;
	if (infile[1] || res[0][0] == '<')
		extract_infile(&lst->data[i++], res, infile);
	if (infile[1])// || (res[0][0] == '<' && has_more_str(infile[0], " \t\n\v\f\r")))
		extract_cmd_head(&lst->data[i++], res, infile);
	/* pipes */
	if (infile[1])// || (res[0][0] == '<' && has_more_str(infile[0], " \t\n\v\f\r") && !has_more_str(infile[0], ">"))) /* && no outfile in 1st line*/
	{
		x = 1;
		if (res[1])
			extract_outfile(&lst->data[i++], "|"); /*add pipe*/
	}
	/*----------- copy in betweens -----------*/
	/* infile[1] for to apply only when there's infile */
	/* for this condition, extract_cmd_head should do the extracting including > outfile */
	/* cmd1 -f -g < infile */
	/* < infile cmd1 -f -g */
	/* < infile | cmd1 -f -g */
	/* < infile */

	process_cmd_tail(&lst->data[i], &res[x]);

	// printf("------\nres:\n");
	// debug_print(res);
	printf("------\ninfile:\n");
	debug_print(infile);
	// printf("------\noutfile:\n");
	// debug_print(outfile);
}

// 24 lines so far
/*
 * splits input by PIPE & REDIR, stores result in allocated t_token pointer
 * uses malloc
 */
void	get_cmd_line(char *str, t_token *lst)
{
	int		count;
	char	*new;
	char	**infile;
	char	**res;

	if (!str || !str[0])
		return ;
	while (is_target(" \t\n\v\f\r", str[0]))
		str++;
	/* ---------------- format string ---------------- */
	/* search & truncate string to last infile < sign */
	/* removes env (VAR="1 2 3") during get_cmds*/
	new = truncate_input(str);
	res = ft_split_shell(new, "|");
	infile = ft_split_shell(res[0], "<");
	if (!res || !infile)
		return ;

	/* ---------------- get_malloc_size ---------------- */
	count = get_malloc_size(res, infile);
	/*debug*/printf("trunc=%s\ncount=%d+1\n", new, count);
	if (!init_token_list(lst, (count + 1)))
		return ;

	printf("------\nres:\n");
	debug_print(res);
	/* ---------------- extract_cmd ---------------- */
	process_cmd(lst, res, infile);
	// assign_datatype(lst, res);

	printf("------\nlst_data:\n");
	debug_print(lst->data);
	/*-------------debug_start-------------*/
	// printf("\n-------\n");
	// int i = -1;
	// while (++i < count_op + 2)
	// 	printf("%s| \n", lst->data[i]);//, lst->datatype[i]);
	/*--------------debug_end--------------*/
	free_multiple_ptr(2, res, infile);
}
