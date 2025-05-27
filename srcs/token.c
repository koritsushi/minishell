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

/*
 * child function in copy_cmd_tail
 * overwrites any < infiles to ' ' spaces
 */
static void	overwrite_infile(char **cmd_tail)
{
	char	*str;
	char	symbol;
	int		flag;

	str = *cmd_tail;
	flag = 0;
	while (str[0])
	{
		update_flag_quote(str, "\'\"", &symbol, &flag);
		if (!flag && str[0] == '<')
		{
			while (is_target("< \t\n\v\f\r", str[0]))
				*str++ = ' ';
			while (!is_target(" \t\n\v\f\r", str[0]))
				*str++ = ' ';
		}
		else
			str++;
	}
}

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
		cmd_tail = skip_consecutive_redir(cmd_tail, 0);

		if (is_target(cmd_tail, '<'))
			overwrite_infile(&cmd_tail);

		// >out <in <in2 cmd
		// out
		// in cmd1
		// in2 cmd2

		// >out cmd<in <in2
		// out cmd
		// in
		// in2

		// /*debug*/printf("***cmd_tail=%s| %zu\n", cmd_tail, ft_strlen(cmd_tail));
		// /*debug*/printf("copy_cmd_tail:%s.\n", cmd_tail);
		if (cmd_tail && cmd_tail[0])
		{
			cmd_tail -= 1;
			ft_strlcpy(&(*lst_data)[(*start)], cmd_tail, ft_strlen(cmd_tail) + 1);
			(*start) += ft_strlen(cmd_tail);
		}
	}
}

/*
 * child function in skip_consecutive_infile
 * skips all spaces after c
 * breaks if found spaces when flag is off
 */
static char	*skip_consecutive(char *str, char *c)
{
	char	symbol;
	int		flag_quote;

	flag_quote = 0;
	while (str && str[0])
	{
		// /*debug*/printf("skip_cons:%s.\n", str);
		update_flag_quote(str, "\'\"", &symbol, &flag_quote);
		// if (str[0] == c[0] || str[0] == '>')
		if (is_target("<>", str[0]))
			str = skip_spaces(str, "<> \t\n\v\f\r");
		else if (is_target(" \t\n\v\f\r", str[0]))
		{
			str = skip_spaces(str, " \t\n\v\f\r");
			if (!flag_quote && str[0] != c[0])
				return (str);
		}
		else
			str++;
	}
	return (str);
}

/*
 * skips all consecutive infiles
 * if flag=1, skip >outfile
 */
char	*skip_consecutive_redir(char *outfile, int flag)
{
	char	*str;

	if (!outfile || !outfile[0])
		return (outfile);
	if (flag)
		str = skip_consecutive(outfile, ">");
	else
		str = outfile;
	if (str[0] == '<')
		str = skip_consecutive(str, "<");
	return (str);

}

// 23 lines!
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
	char	*cmd_tail;

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
	// /*debug*/printf("extract_cmd_tail:ent:%s.\n", str);
	start = 0;
	if (str[0] == '>')
	{
		// /*debug*/printf("ext_cmdt:out:%s.\n", outfile[0]);
		cmd_tail = skip_spaces(outfile[0], " \t\n\v\f\r");
		cmd_tail = skip_consecutive_redir(cmd_tail, 1);
		if (!cmd_tail || !cmd_tail[0])
			return ;
	}
	else
		cmd_tail = outfile[0];
	// /*debug*/printf("extract_cmd_tail:%s.\n", cmd_tail);

	if (!allocate_cmd_tail(&lst_data[*i], outfile, cmd_tail))
		return ;
    /* copy cmd_head */
	// if (str[0] != '>')
	// {
	infile_check = ft_split_shell(cmd_tail, "<");
	// infile_check = ft_split_shell(outfile[0], "<");
	// /*debug*/printf("___infile_check:___\n");
	// /*debug*/debug_print(infile_check);
	start = ft_strlcpy(lst_data[(*i)], infile_check[0], ft_strlen(infile_check[0]) + 1);
	copy_cmd_tail(&lst_data[(*i)], &start, &infile_check[1]);
	free_chr_ptr((void **)infile_check);
	// }
	/* copy cmd_tail*/
	if (outfile[1])
		copy_cmd_tail(&lst_data[(*i)], &start, &outfile[1]);
	// /*debug*/printf("tail_fin=%s.\n", lst_data[(*i)]);
	*i += 1;
}

// 16 lines!
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

	/*__________start_here_________*/
	cmd_tail = skip_consecutive_redir(cmd_tail, 0);
	if (!cmd_tail || !cmd_tail[0])
		return ;
	// /*debug*/printf("cmd_tail:%s.\n", cmd_tail);

	outfile = ft_split_shell(cmd_tail, ">");
	// /*debug*/printf("------\np_cmd_t:outfile:\n");
	// /*debug*/debug_print(outfile);
	// /*debug*/printf("------\nprocess_cmd_tail:%s.\n", cmd_tail);

	if (!outfile || !outfile[0])
		return ;
	extract_cmd_tail(lst_data, i, cmd_tail, outfile);
	free_chr_ptr((void **)outfile);
}

// 16 lines!
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
	x = -1;
	while (res && res[++x])
	{
		/*----------- get_infiles -----------*/
		cmd_tail = skip_spaces(res[x], " \t\n\v\f\r");
		// /*debug*/printf("cmd_tail:ent:%s.\n", cmd_tail);

		if (ft_strchr(cmd_tail, '<'))
			extract_infile(lst->data, &i, cmd_tail);

		process_cmd_tail(lst->data, &i, cmd_tail);
		process_outfile(lst->data, &i, cmd_tail);
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

	// /*debug*/printf("get_cmd_line:\033[93mcount=%d+1\033[0m, %s.\n", count, str);
	// /*debug*/printf("------\nres:\n");
	// /*debug*/debug_print(res);
	/* ---------------- extract_cmd ---------------- */
	process_cmd(lst, res);
	cmd_expansion(lst->data, vars, exit_status);
	assign_datatype(lst->datatype, res);
	add_filler_cmd(lst);
	free_chr_ptr((void **)res);
	return (1);
}
