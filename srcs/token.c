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
	(void)	lst_data;
	(void)	str;
	(void)	outfile;

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
	if (!allocate_cmd_tail(lst_data, outfile, str[0]))
		return ;
	i = 0;
	start = 0;

    /* copy cmd_head */
	if (str[0] != '>')
	{
		/* if str[0] is splittable by infile '<' */
		/* if outfile[0] = cmd <infile in2 in3 >out  */
		infile_check = ft_split_shell(outfile[0], "<");
		/*debug*/printf("___infile_check:___\n");
		/*debug*/debug_print(infile_check);
		start = ft_strlcpy(*lst_data, infile_check[0], ft_strlen(infile_check[0]) + 1);
		copy_cmd_tail(lst_data, &start, &infile_check[1]);
		free_chr_ptr((void **)infile_check);
		i = 1;
	}
	if (outfile[i])
		copy_cmd_tail(lst_data, &start, &outfile[i]);
	/*debug*/printf("tail_fin=%s.\n", *lst_data);
}

// void	extract_cmd_tail(char **lst_data, char *str, char **outfile)
// {
// 	char	**infile_check;
// 	int		start;
// 	int		i;

// 	/* < infile cmd */
// 	/* < infile <infile cmd */
// 	/* < infile cmd cmd */
// 	/* cmd < infile1 infile2 > outfile -k */
// 	/* cmd > outfile -k */

// 	/* cmd3 > outfile -a -b */
// 	/* cmd3 > outfile1 > outfile2 -a -b */
// 	/* > outfile1 > outfile2 -a -b */
// 	/* > outfile1 > outfile2*/

// 	allocate_cmd_tail(lst_data, outfile, str[0]);
// 	i = 0;
// 	start = 0;

//     /* copy cmd_head */
// 	if (str[0] != '>')
// 	{
// 		/* if str[0] is splittable by infile '<' */
// 		infile_check = ft_split_shell(outfile[0], "<");
// 		ft_strlcpy(*lst_data, infile_check[0], ft_strlen(infile_check[0]) + 1);
// 		start = ft_strlen(infile_check[0]);
// 		i = 1;
// 		free_chr_ptr((void **)infile_check);
// 	}
// 	copy_cmd_tail(lst_data, start, &outfile[i]);
// 	// /*debug*/printf("tail_fin=%s\n", *lst_data);//, &(*lst_data)[start-3]);
// }

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
	(void)	i;
	(void)	lst_data;

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

	if (outfile[0] && outfile[1] && (cmd_tail[0] != '>' || \
		(cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))))
		extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
	// /* if not > splittable */
	else if (outfile[0] && !outfile[1])
	{
		/* if begin with >, check if has_more_str_all */
		/* if theres no <>, only single cmd, copy over */
		/* if begin with < (one_line_condition), do not extract */
		// /*debug*/printf("extract_cmd_tail:%s\n", cmd_tail);
		if (cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r")) // >out cmd
			extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
		else if (cmd_tail[0] && !is_target("<>", cmd_tail[0])) // normal plain cmd
			extract_cmd_tail(&lst_data[(*i)++], cmd_tail, outfile);
	}

	// /*--------------extract outfiles--------------*/
	process_outfile(lst_data, i, cmd_tail, outfile);
	free_chr_ptr((void **)outfile);
}

// 22 lines!
/*
 * scans line and saves valid command into a new char** array, str=new
 * uses malloc
 */
void	process_cmd(t_token *lst, char **res)//, char **infile)
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

/*
 * child function in check_copy_data
 * copies respective data
 */
void	copy_data(t_token *dest, int *k, char *lst_data, \
unsigned char lst_datatype)
{
	dest->data[*k] = ft_strdup(lst_data);
	dest->datatype[(*k)++] = lst_datatype;
}

//24 lines!
/*
 * child function in add_filler_cmd
 * add empty string or copy respective data
 */
static void	check_copy_data(t_token *lst, t_token *dest, int flag)
{
	int	x;
	int	k;

	x = -1;
	k = 0;
	while (lst->data[++x])
	{
		// flag_cmd refresh by pipes

		// <infile | cmd | >outfile >out2 | cmd
		// <infile “” | cmd | >outfile >out2 | cmd
		if (lst->datatype[x] == WORD)
			flag = 1;
		if (!flag && (lst->datatype[x] == PIPE || \
(lst->datatype[x] == OUTFILE || lst->datatype[x] == OUTFILE_A)))
		{
			if ((lst->datatype[x] == OUTFILE || lst->datatype[x] == OUTFILE_A))
				flag = 1;
			copy_data(dest, &k, "", WORD);
			copy_data(dest, &k, lst->data[x], lst->datatype[x]);
		}
		else
			copy_data(dest, &k, lst->data[x], lst->datatype[x]);
		if (!flag && lst->data[x + 1] == NULL)
		{
			/*debug*/printf("pikapi %d\n", k);
			copy_data(dest, &k, "", WORD);
		}
		if (flag && lst->datatype[x] == PIPE) //reset
			flag = 0;
	}
}

/* counts +=1 if there is no cmd in a pipe */
static int	count_realloc(t_token lst)
{
	int	x;
	int	flag;
	int	count;

	x = -1;
	flag = 0;
	count = 0;
	while (lst.data[++x])
	{
		// <infile | cmd | >outfile >out2 | cmd
		// <infile “” | cmd | >outfile >out2 | cmd

		if (lst.datatype[x] == WORD)
			flag = 1;
		else if (!flag && (lst.datatype[x] == OUTFILE || lst.datatype[x] == OUTFILE_A))
		{
			flag = 1;
			count++;
		}
		else if (!flag && (lst.datatype[x] == PIPE || lst.data[x + 1] == NULL))
			count++;
		if (flag && lst.datatype[x] == PIPE)
			flag = 0;
		// /*debug*/printf("x:%d  count:%d  f:%d\n", x, count, flag);
	}
	return (count);
}

/*
 * child function in get_cmd_line
 * checks if a pipe has no cmd,
 * if true, adds a empty string "" for execution purposes
 */
void	add_filler_cmd(t_token *lst)
{
	//int		x;
	int		count;
	t_token	dest;

	//x = -1;
	count = count_realloc(*lst);
	/*debug*/printf("add_filler_cmd:%d\n", count);
	if (!count)
		return ;
	count += count_str_array(lst->data);
	/*debug*/printf("add_filler:malloc: %d+1\n", count);

	if (!init_token_list(&dest, count + 1))
		return ;
	check_copy_data(lst, &dest, 0);
	// /*debug*/printf("\033[92m___add_filler_cmd:___\033[0m");
	// /*debug*/debug_print_cmd_line(&dest);
	free_all(lst);
	lst->data = dest.data;
	lst->datatype = dest.datatype;
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
