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

//24 lines passed!
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
		while (infile_fin[i + 1])
			i++;
	}
	allocate_str(lst_data, infile_fin[i]);
	ft_strlcpy(*lst_data, infile_fin[i], ft_strlen(infile_fin[i]) + 1);

	printf("------\ninfile:\n");
	debug_print(infile);
	printf("------\nINFILE=%s\n", *lst_data);

	free_chr_ptr((void **)infile_fin);
}

/*
 * get & saves outfile string into lst_data
 */
// void	extract_outfile(char **lst_data, char **outfile)
// {
// 	int		i;
// 	char	**outfile_fin;

// 	printf("------\noutfile:\n");
// 	debug_print(outfile);

// 	i = 0;
// 	while(outfile[i + 1])
// 		i++;
// 	outfile_fin = ft_split_shell(outfile[i], " \t\n\v\f\r");
// 	allocate_str(outfile_fin[0], lst_data);
// 	ft_strlcpy(*lst_data, outfile_fin[0], ft_strlen(outfile_fin[0]) + 1);

// 	printf("------\noutfile_fin:\n");
// 	debug_print(outfile_fin);
// 	printf("------\nOUTFILE=%s\n", *lst_data);

// 	free_chr_ptr((void **)outfile_fin);
// }

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

/* extracts command properly skipping the infiles */
/* can update **res to *str (follow extract_cmd_tail)*/
void	extract_cmd_head(char **lst_data, char **res, char **infile)
{
	char	*cmd_head;
	char	**cmd_head_fin;

	cmd_head = infile[0];
	while (is_target(" \t\n\v\f\r", cmd_head[0]))
		cmd_head++;
	if (res[0][0] == '<')
	{
		cmd_head = ft_strchr(cmd_head, ' ');
		while (is_target(" \t\n\v\f\r", cmd_head[0]))
			cmd_head++;
	}
	cmd_head_fin = ft_split_shell(cmd_head, ">");
	allocate_str(lst_data, cmd_head_fin[0]);
	ft_strlcpy(*lst_data, cmd_head_fin[0], ft_strlen(cmd_head_fin[0]) + 1);
	free_chr_ptr((void **)cmd_head_fin);
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

	/* if '>' && !has_more_str_all, skip*/
	/* if !'>' || (if '>' && has_more_str_all) */
	allocate_cmd_tail(lst_data, outfile);
	if (str[0] != '>')
	{
		/* copy outfile[0] */
		/* skips to the 1st space detected */
	}
	if (str[0] == '>')
	{
		/* skips spaces */
		/* skips to the 1st space detected */
	}
	i = 0;
	if (str[0] != '>')
	{
		ft_strlcpy(*lst_data, outfile[0], ft_strlen(outfile[0]) + 1);
		start = ft_strlen(outfile[0]);
		i = 1;
	}
	/* if theres outfile*/
	while (outfile[i])
	{
		cmd_tail = outfile[i];
		/* travel to the first space detected */
		while (cmd_tail[0] && is_target(" \t\n\v\f\r", cmd_tail[0]))
			cmd_tail++;
		cmd_tail = ft_strchr(cmd_tail, ' ');
		/*debug*/printf("***cmd_tail=%s\n", cmd_tail);
		if (!cmd_tail)
			break ;
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
	char	*tmp;

	x = 0;
	i = 0;
	while (res[x])
	{
		tmp = res[x];
		/* if there's space, skip */
		while (is_target(" \t\n\v\f\r", tmp[0]))
			tmp++;
		outfile = ft_split_shell(tmp, ">");
		/* cmd > outfile1 */
		/* cmd > outfile1 -k */
		/* > outfile1 > outfile2 */
		/* > outfile1 cmd */
		/* cmd */
		/* < infile cmd */

		/*debug*/printf("------\noutfile:\n");
		/*debug*/debug_print(outfile);

		/*--------------extract cmd_tail--------------*/
		/* if splittable && has_more_str_all*/
		if (outfile[1] && tmp[0] != '>')
			extract_cmd_tail(&lst_data[i++], tmp, outfile);
		/* if not splittable */
		else if (!outfile[1])
		{
			/* if begin with >, check if has_more_str_all */
			/* if theres no <>, only single cmd, copy over */
			/* if begin with < (one_line_condition), do not extract */
			if (tmp[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))
				extract_cmd_tail(&lst_data[i++], tmp, outfile);
			if (tmp[0] != '<')
				extract_cmd_tail(&lst_data[i++], tmp, outfile);
		}
		
		/*--------------extract outfiles--------------*/
		/* if start with '>' */
		if (tmp[0] == '>')
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
	if (infile[1] || (res[0][0] == '<' && has_more_str(infile[0], " \t\n\v\f\r")))
		extract_cmd_head(&lst->data[i++], res, infile);
	if (infile[1] || (res[0][0] == '<' && has_more_str(infile[0], " \t\n\v\f\r") && !has_more_str(infile[0], ">"))) /* && no outfile in 1st line*/
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
	// process_cmd(lst, res, infile);
	// // assign_datatype(lst, res);

	// printf("------\nlst_data:\n");
	// debug_print(lst->data);
	/*-------------debug_start-------------*/
	// printf("\n-------\n");
	// int i = -1;
	// while (++i < count_op + 2)
	// 	printf("%s| \n", lst->data[i]);//, lst->datatype[i]);
	/*--------------debug_end--------------*/
	free_multiple_ptr(2, res, infile);
}
