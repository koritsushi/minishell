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
// #include "includes/expansion.h"

// 15 lines!
/* scans through line and copies correct cmds */
void	copy_cmd_tail(char **lst_data, int start, char **outfile)
{
	char	*cmd_tail;
	int		i;

	i = 0;
	while (outfile[i])
	{
		/* travel to the first space detected */
		cmd_tail = skip_spaces(outfile[i], " \t\n\v\f\r");
		cmd_tail = ft_strchr(cmd_tail, ' ');
		cmd_tail = skip_spaces(cmd_tail, " \t\n\v\f\r");
		// /*debug*/printf("***cmd_tail=%s| %zu\n", cmd_tail, ft_strlen(cmd_tail));
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
}

// 16 lines!
/* 
 * child function of process_cmd_tail
 * allocates enough space to store cmd and copies it
 * str = the entire line of cmd/pipeline before splitted by outfile '>'
 * uses malloc
 */
void	extract_cmd_tail(char **lst_data, char *str, char **outfile)
{
	char	**infile_check;
	int		start;
	int		i;

	/* < infile cmd */
	/* < infile <infile cmd */
	/* < infile cmd cmd */
	/* cmd < infile1 infile2 > outfile -k */
	/* cmd > outfile -k */

	/* cmd3 > outfile -a -b */
	/* cmd3 > outfile1 > outfile2 -a -b */
	/* > outfile1 > outfile2 -a -b */
	/* > outfile1 > outfile2*/

	allocate_cmd_tail(lst_data, outfile, str[0]);
	i = 0;
	start = 0;

    /* copy cmd_head */
	if (str[0] != '>')
	{
		/* if str[0] is splittable by infile '<' */
		infile_check = ft_split_shell(outfile[0], "<");
		ft_strlcpy(*lst_data, infile_check[0], ft_strlen(infile_check[0]) + 1);
		start = ft_strlen(infile_check[0]);
		i = 1;
		free_chr_ptr((void **)infile_check);
	}
	copy_cmd_tail(lst_data, start, &outfile[i]);
	// /*debug*/printf("tail_fin=%s\n", *lst_data);//, &(*lst_data)[start-3]);
}

// 15 lines!
/* child function in process_cmd, *i = lst_data index number */
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
	
	/* < infile < in2 cmd > outfile */

	/* cmd < infile > outfile */
	/* cmd > outfile */

	/*__________start_here_________*/
	outfile = ft_split_shell(cmd_tail, ">");

	// /*debug*/printf("------\noutfile:\n");
	// /*debug*/debug_print(outfile);

	// if cmd_tail[0] == '<' , skip all infiles
	// split by '>'

	/*--------------extract_cmd_tail--------------*/
	/* if splittable && has_more_str_all*/
	if (outfile[1] && (cmd_tail[0] != '>' || \
		(cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))))
		extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
	/* if not splittable */
	if (!outfile[1])
	{
		/* if begin with >, check if has_more_str_all */
		/* if theres no <>, only single cmd, copy over */
		/* if begin with < (one_line_condition), do not extract */
		// /*debug*/printf("extract_cmd_tail:%s\n", cmd_tail);
		if (cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))
			extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
		if (cmd_tail[0] && !is_target("<>", cmd_tail[0]))
			extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
	}

	/*--------------extract outfiles--------------*/
	process_outfile(lst_data, i, cmd_tail, outfile);
	free_chr_ptr((void **)outfile);
}

// void	process_cmd_tail(char **lst_data, int *i, char *cmd_tail)
// {
// 	char	**outfile;

// 	/*__________splittable_________*/
// 	/* < infile cmd > outfile */
// 	/* < infile > outfile */
// 	/* cmd > outfile1 */
// 	/* cmd > outfile1 -k */
// 	/* > outfile1 > outfile2 */
// 	/* > outfile1 cmd1 > outfile2 -h */
// 	/* > outfile1 cmd1 */

// 	/*__________!splittable_________*/
// 	/* >       outfile1 cmd */
// 	/* > outfile1 cmd */
// 	/* cmd */
// 	/* < infile cmd */
// 	/* < infile <infile cmd */
// 	/* cmd < infile1 infile2 -k */
	
// 	/* cmd < infile > outfile */
// 	/* < infile cmd > outfile */

// 	/*__________start_here_________*/
// 	outfile = ft_split_shell(cmd_tail, ">");

// 	// /*debug*/printf("------\noutfile:\n");
// 	// /*debug*/debug_print(outfile);

// 	/*--------------extract_cmd_tail--------------*/
// 	/* if splittable && has_more_str_all*/
// 	if (outfile[1] && (cmd_tail[0] != '>' || \
// 		(cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))))
// 		extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
// 	/* if not splittable */
// 	if (!outfile[1])
// 	{
// 		/* if begin with >, check if has_more_str_all */
// 		/* if theres no <>, only single cmd, copy over */
// 		/* if begin with < (one_line_condition), do not extract */
// 		// /*debug*/printf("extract_cmd_tail:%s\n", cmd_tail);
// 		if (cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))
// 			extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
// 		if (cmd_tail[0] && !is_target("<>", cmd_tail[0]))
// 			extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
// 	}

// 	/*--------------extract outfiles--------------*/
// 	process_outfile(lst_data, i, cmd_tail, outfile);
// 	free_chr_ptr((void **)outfile);
// }

// 18 lines!
/*
 * scans line and saves valid command into a new char** array, str=new
 * uses malloc
 */
void	process_cmd(t_token *lst, char **res, char **infile)
{
	int		i;
	int		x;
	char	*cmd_tail;
	(void)	infile;

	/*----------- get_infiles -----------*/
	i = 0;
	// if (infile[1] || res[0][0] == '<')
		// extract_infile(&lst->data[i++], res, infile);

	/*----------- copy the rest -----------*/
	/* cmd1 -f -g < infile */
	/* < infile cmd1 -f -g */
	/* < infile | cmd1 -f -g */
	/* < infile */

	x = -1;
	while (res && res[++x])
	{
		if (ft_strchr(res[x], '<'))
			extract_infile(lst->data, &i, res[x]);
		// /*debug*/printf("process_cmd:i:%d\n", i);
		cmd_tail = skip_spaces(res[x], "< \t\n\v\f\r");
		cmd_tail = skip_if_symbol(cmd_tail, res[x][0], '<');
		if (!cmd_tail)
			break ;
		// process_cmd_tail(lst->data, &i, cmd_tail);
		// // /*------------ add_pipes ------------*/
		// if (res[x + 1])
		// 	extract_outfile(&lst->data[i++], "|");
		// i++;
	}

	// /*debug*/ printf("------\ninfile:\n");
	// /*debug*/ debug_print(infile);
}

// 21 lines so far
/*
 * splits input by PIPE & REDIR, stores result in allocated t_token pointer
 * uses malloc
 */
int	get_cmd_line(char *str, t_token *lst, t_env *vars, int exit_status)
{
	int		count;
	char	*new;
	char	**infile;
	char	**res;
	(void)	vars;
	(void)	exit_status;

	str = skip_spaces(str, " \t\n\v\f\r");
	if (!str || !str[0])
		return (0);
	/* ---------------- format string ---------------- */
	/* search & truncate string to last infile < sign */
	/* removes env (VAR="1 2 3") during get_cmds*/
	// new = truncate_input(str);
	new = str;
	res = ft_split_shell(new, "|");
	infile = ft_split_shell(res[0], "<");
	if (!res || !infile)
		return (0);

	/* ---------------- get_malloc_size ---------------- */
	count = get_malloc_size(res);//, infile);
	if (!init_token_list(lst, (count + 1)))
		return (0);

	// /*debug*/printf("trunc=%s\n", new);
	/*debug*/printf("get_cmd_line:\033[93mcount=%d+1\033[0m, %s.\n", count, new);
	// /*debug*/printf("------\nres:\n");
	// /*debug*/debug_print(res);
	/* ---------------- extract_cmd ---------------- */
	process_cmd(lst, res, infile);
	// cmd_expansion(lst->data, vars, exit_status); //exit status need to redef
	// assign_datatype(lst->datatype, res, infile);

	/*-------------debug_start-------------*/
	// printf("\n\033[102m_____lst_data:_____\033[0m\n");
	// int i = -1;
	// // while (lst->data[++i])
	// while (++i < count)
	// 	printf("\033[92m%s\033[0m. [%d]\n", lst->data[i], lst->datatype[i]);
	/*--------------debug_end--------------*/

	free_multiple_ptr(res, infile, NULL);
	return (1);
}
