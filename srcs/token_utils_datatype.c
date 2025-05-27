/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_datatype.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 07:55:00 by hsim              #+#    #+#             */
/*   Updated: 2025/05/27 22:10:54 by hsim             ###   ########.fr       */
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

	/* use ft_strchr */
	/* > out1 cmd */
	/* > out1 > out2 cmd */
	/* cmd > out1 > out2 */

	/* check the entire string */
	cmd_tail = str;
	while (cmd_tail && cmd_tail[0])
	{
		cmd_tail = ft_strchr(cmd_tail, '>');
		// /*debug*/printf("datatype=%s\n", cmd_tail);
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

	infile = ft_split_shell(cmd_tail, "<");
	if (!infile)
		return ;
	// <in cmd <in2
	// cmd <in cmd <in2
	// <in cmd
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
static void	assign_datatype_cmd_tail(char *str, unsigned char *datatype, \
int *i, char **outfile)
{
	char	*cmd_tail;

	cmd_tail = str;	
	/* if splittable */
	if (outfile[1] && (cmd_tail[0] != '>' || \
(cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))))
		datatype[(*i)++] = WORD;
		/* if not splittable && has_more_str_all */
		// else if (!outfile[1] && has_more_str_all(outfile, " \t\n\v\f\r"))
	else if (!outfile[1])
	{
		/* cmd1 cmd2 */
		/* cmd1 */
		/* > out1 cmd */
		/* if begin with >, check if has_more_str_all */
		/* if theres no <>, only single cmd, copy over */
		/* if begin with < (one_line_condition), do not extract */
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

	/* cmd1 -f -g < infile */
	/* cmd1 -f -g < infile < infile2 */
	/* < infile < infile2 cmd */
	/* < infile cmd1 -f -g */
	/* < infile | cmd1 -f -g */
	/* < infile cmd > outfile */
	/* cmd */

	/* cmd < infile > outfile */
	/* < infile */

	i = 0;
	x = -1;
	/* _____________get infile_____________ */
	/* if infile[1], travel to the last infile '<' */

	// <in1 in2 in3   <in4 cmd
	// cmd            <in1 in2 in3 <in4
	// <in4 cmd
	// cmd_tail = search_rstr(res[0], '<', ft_strlen(res[0]));
	// /*debug*/printf("assign_datatype:%s.\n", cmd_tail);
	// if (infile[1])
	// 	assign_datatype_infile(cmd_tail, datatype, &i);
	// else if (!infile[1] && cmd_tail[0] == '<')
	// 	assign_datatype_infile(cmd_tail, datatype, &i);

		/* get the rest */
	// <in1 in2 cmd | <in3 blabla
	while (res[++x])
	{
		//get infile here
		// <in1 in2  <in4  cmd    splittable
		// cmd <in1 in2 in3 <in4
		cmd_tail = skip_spaces(res[x], " \t\n\v\f\r");
		assign_datatype_infile(cmd_tail, datatype, &i);
		/* skip spaces & infile symbol */
		cmd_tail = skip_redirs(cmd_tail);

		// /*debug*/printf("assign_datatype:tail:%s.\n", cmd_tail);
		outfile = ft_split_shell(cmd_tail, ">");
		if (!outfile)
		{
			// /*debug*/printf("!outfile assign_datatype!\n");
			break ;
		}
		assign_datatype_cmd_tail(cmd_tail, datatype, &i, outfile);
		assign_datatype_outfile(res[x], datatype, &i);
		if (res[x + 1])
			datatype[i++] = PIPE;
		free_chr_ptr((void **)outfile);
	}
}
