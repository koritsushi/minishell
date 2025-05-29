/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_datatype.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 07:55:00 by hsim              #+#    #+#             */
/*   Updated: 2025/05/29 18:16:57 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/* 
 * checks if str[0] is '>' or '>>' ,
 * returns datatype result in unsigned char *datatype
 */
static void	assign_datatype_outfile(char *str, unsigned char *datatype, int *i)
{
	char	*cmd_tail;

	cmd_tail = str;
	while (cmd_tail && cmd_tail[0])
	{
		cmd_tail = ft_strchr(cmd_tail, '>');
		if (!cmd_tail)
			break ;
		if (cmd_tail[1] == '>')
		{
			datatype[(*i)++] = OUTFILE_A;
			cmd_tail++;
		}
		else if (cmd_tail[0] == '>')
			datatype[(*i)++] = OUTFILE;
		cmd_tail++;
	}
}

/*
 * child function in assign_datatype_infile
 * checks if str[0] is '<' or '<<' , returns result
 */
static void	assign_infile_now(char **infile, char *cmd_tail, \
unsigned char *datatype, int *i)
{
	int		x;

	x = -1;
	if (!cmd_tail)
		return ;
	while (infile[++x])
	{
		if (cmd_tail[0] == '<' && cmd_tail[1] == '<')
		{
			datatype[(*i)++] = HEREDOC;
			cmd_tail = ft_strchr(cmd_tail + 2, '<');
		}
		else if (cmd_tail[0] == '<' && cmd_tail[1] != '<')
		{
			datatype[(*i)++] = INFILE;
			cmd_tail = ft_strchr(cmd_tail + 1, '<');
		}
	}
}

/* child function in assign_datatype */
static void	assign_datatype_infile(char *cmd_tail, unsigned char *datatype, \
int *i)
{
	char	**infile;

	if (!cmd_tail || !cmd_tail[0])
		return ;
	infile = ft_split_shell(cmd_tail, "<");
	if (!infile)
		return ;
	if (infile[1] && cmd_tail[0] == '<')
		assign_infile_now(infile, cmd_tail, datatype, i);
	else if (infile[1] && cmd_tail[0] != '<')
		assign_infile_now(&infile[1], ft_strchr(cmd_tail, '<'), datatype, i);
	else if (!infile[1] && cmd_tail[0] == '<')
		assign_infile_now(infile, cmd_tail, datatype, i);
	free_chr_ptr((void **)infile);
}

/*
 * child function in assign_datatype
 * checks if str[0] is WORD, str[0] = cmd_tail
 */
static void	assign_datatype_cmd_tail(\
char *str, unsigned char *datatype, int *i, char **outfile)
{
	char	*cmd_tail;

	if (!str || !str[0] || !outfile)
		return ;
	cmd_tail = skip_redirs(str);
	if (!cmd_tail || !cmd_tail[0])
		return ;
	if (outfile[1] && (cmd_tail[0] != '>' || \
(cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))))
		datatype[(*i)++] = WORD;
	else if (!outfile[1])
	{
		if (cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))
			datatype[(*i)++] = WORD;
		else if (cmd_tail[0] && cmd_tail[0] != '>')
			datatype[(*i)++] = WORD;
	}
}

// 22 lines!
/*
 * considered as lexing process
 * scans input and assigns datatype according to operator sign
 */
void	assign_datatype(unsigned char *datatype, char **res)
{
	int		x;
	int		i;
	char	*cmd_tail;
	char	**outfile;

	i = 0;
	x = -1;
	while (res[++x])
	{
		cmd_tail = skip_spaces(res[x], " \t\n\v\f\r");
		assign_datatype_infile(cmd_tail, datatype, &i);
		cmd_tail = skip_consecutive_redir(cmd_tail, 0);
		if (cmd_tail && cmd_tail[0])
		{
			outfile = ft_split_shell(cmd_tail, ">");
			assign_datatype_cmd_tail(cmd_tail, datatype, &i, outfile);
			assign_datatype_outfile(res[x], datatype, &i);
			free_chr_ptr((void **)outfile);
		}
		if (res[x + 1])
			datatype[i++] = PIPE;
	}
}
