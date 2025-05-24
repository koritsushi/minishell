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

// 15 lines!
/*
 * child function in extract_cmd_tail
 * scans through line and copies the correct cmds
 */
void	copy_cmd_tail(char **lst_data, int *start, char **outfile)
{
	char	*cmd_tail;
	int		i;

	i = -1;
	if (!outfile)
		return ;
	while (outfile[++i])
	{
		/* travel to the first space detected */
		cmd_tail = skip_spaces(outfile[i], " \t\n\v\f\r");
		cmd_tail = skip_if_symbol(cmd_tail, 'c', 'c');

		// /*debug*/printf("***cmd_tail=%s| %zu\n", cmd_tail, ft_strlen(cmd_tail));
		/*debug*/printf("copy_cmd_tail:%s.\n", cmd_tail);
		/* copy to array */
		if (cmd_tail && cmd_tail[0])
		{
			ft_strlcpy(&(*lst_data)[(*start)], cmd_tail, ft_strlen(cmd_tail) + 1);
			(*start) += ft_strlen(cmd_tail);
		}
	}
}

// 19 lines!
/* 
 * child function of process_cmd_tail
 * allocates enough space to store cmd and copies it
 * str = the entire line of cmd/pipeline before splitted by outfile '>'
 * uses malloc
 */
void	extract_cmd_tail(char **lst_data, int *i, char *str, char **outfile)
{
	char	**infile_check;
	int		start;
	int		k;

	/* < infile cmd */
	/* < infile <infile cmd */
	/* < infile cmd cmd */
	/* cmd < infile1 infile2 > outfile -k */
	/* cmd > outfile -k */

	/* cmd3 > outfile -a -b */
	/* cmd3 > outfile1 > outfile2 -a -b */
	/* > outfile1 > outfile2 -a -b */
	/* > outfile1 > outfile2*/

	// skip space
	// skip symbol '>'
	// skip redirs '<>'
	if (!allocate_cmd_tail(&lst_data[*i], outfile, str[0]))
		return ;
	k = 0;
	start = 0;

    /* copy cmd_head */
	if (str[0] != '>')
	{
		/* if str[0] is splittable by infile '<' */
		/* if outfile[0] = cmd <infile in2 in3 >out  */
		infile_check = ft_split_shell(outfile[0], "<");
		/*debug*/printf("___infile_check:___\n");
		/*debug*/debug_print(infile_check);
		start = ft_strlcpy(lst_data[(*i)], infile_check[0], ft_strlen(infile_check[0]) + 1);
		copy_cmd_tail(&lst_data[(*i)], &start, &infile_check[1]);
		free_chr_ptr((void **)infile_check);
		k = 1;
	}
	if (outfile[k])
		copy_cmd_tail(&lst_data[(*i)], &start, &outfile[k]);
	/*debug*/printf("tail_fin=%s.\n", lst_data[(*i)]);
	*i += 1;
}

// 17 lines!
/*
 * child function in process_cmd, *i = lst_data index number
 * for !outfile[1]
 * if begin with >, check if has_more_str_all
 * if theres no <>, only single cmd, copy over
 * if begin with < (one_line_condition), do not extract
 */
void	process_cmd_tail(char **lst_data, int *i, char *cmd_tail)
{
	char	**outfile;

	/*__________splittable_________*/
	/* < infile cmd > outfile */
	/* < infile > outfile */
	/* cmd > outfile1 */
	/* cmd > outfile1 -k */
	/* > outfile1 > outfile2 */
	/* > outfile1 cmd1 > outfile2 -h */
	/* > outfile1 cmd1 */

	/*__________!splittable_________*/
	/* >       outfile1 cmd */
	/* > outfile1 cmd */
	/* cmd */
	/* < infile cmd */
	/* < infile <infile cmd */
	/* cmd < infile1 infile2 -k */

	/*__________start_here_________*/
	if (!cmd_tail || !cmd_tail[0])
		return ;
	outfile = ft_split_shell(cmd_tail, ">");

	/*debug*/printf("------\noutfile:\n");
	/*debug*/debug_print(outfile);
	/*debug*/printf("------\nprocess_cmd_tail:%s.\n", cmd_tail);
	
	/* < infile < in2 cmd        > outfile */
	/* cmd < infile <in2 <in3    > outfile */

	/*--------------extract_cmd_tail--------------*/
	/* if splittable by > && has_more_str_all*/
	// >out >out some_cmd
	extract_cmd_tail(lst_data, i, cmd_tail, outfile);
	// extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);

	// if (outfile[0] && outfile[1] && (cmd_tail[0] != '>' || \
	// 	(cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))))
	// 	extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
	// // /* if not > splittable */
	// else if (outfile[0] && !outfile[1])
	// {
	// 	/* if begin with >, check if has_more_str_all */
	// 	/* if theres no <>, only single cmd, copy over */
	// 	/* if begin with < (one_line_condition), do not extract */
	// 	// /*debug*/printf("extract_cmd_tail:%s\n", cmd_tail);
	// 	if (cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r")) // >out cmd
	// 		extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
	// 	else if (cmd_tail[0] && !is_target("<>", cmd_tail[0])) // normal plain cmd
	// 		extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
	// }

	// /*--------------extract outfiles--------------*/
	process_outfile(lst_data, i, cmd_tail, outfile);
	free_chr_ptr((void **)outfile);
}

// 20 lines!
/*
 * scans line and saves valid command into a new char** array, str=new
 * uses malloc
 */
void	process_cmd(t_token *lst, char **res)
{
	int		i;
	int		x;
	char	*cmd_tail;

	i = 0;
	/*----------- copy the rest -----------*/
	/* cmd1 -f -g < infile */
	/* < infile cmd1 -f -g */
	/* < infile | cmd1 -f -g */
	/* < infile */

	x = -1;
	while (res && res[++x])
	{
		/*----------- get_infiles -----------*/
		cmd_tail = skip_spaces(res[x], " \t\n\v\f\r");
		/*debug*/printf("cmd_tail:ent:%s.\n", cmd_tail);

		if (ft_strchr(cmd_tail, '<'))
			extract_infile(lst->data, &i, cmd_tail);
		// /*debug*/printf("process_cmd:i:%d\n", i);

		// skips to where cmd starts & process cmd
		// for scenario '< infile cmd'
		while (cmd_tail && cmd_tail[0] == '<')
		{
			cmd_tail = skip_spaces(cmd_tail, "< \t\n\v\f\r");
			cmd_tail = skip_if_symbol(cmd_tail, 'c', 'c');
		}
		/*debug*/printf("cmd_tail:%s.\n", cmd_tail);
		process_cmd_tail(lst->data, &i, cmd_tail); //include process outfile
		/*------------ add_pipes ------------*/
		if (res[x + 1])
			extract_outfile(&lst->data[i++], "|");
	}
}

// 18 lines so far
/*
 * splits input by PIPE & REDIR, stores result in allocated t_token pointer
 * uses malloc
 */
int	get_cmd_line(char *str, t_token *lst, t_env *vars, int exit_status)
{
	int		count;
	char	**res;
	(void)	vars;
	(void)	exit_status;

	str = skip_spaces(str, " \t\n\v\f\r");
	if (!str || !str[0])
		return (0);
	/* ---------------- format string ---------------- */
	/* search & truncate string to last infile < sign */
	/* removes env (VAR="1 2 3") during get_cmds*/
	res = ft_split_shell(str, "|");
	if (!res)
		return (0);

	/* ---------------- get_malloc_size ---------------- */
	count = get_malloc_size(res);
	if (!init_token_list(lst, (count + 1)))
		return (0);

	/*debug*/printf("get_cmd_line:\033[93mcount=%d+1\033[0m, %s.\n", count, str);
	/*debug*/printf("------\nres:\n");
	/*debug*/debug_print(res);
	/* ---------------- extract_cmd ---------------- */
	process_cmd(lst, res);
	cmd_expansion(lst->data, vars, exit_status);
	assign_datatype(lst->datatype, res);

	add_filler_cmd(lst);
	free_chr_ptr((void **)res);
	return (1);
}
