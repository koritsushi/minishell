/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_datatype.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 07:55:00 by hsim              #+#    #+#             */
/*   Updated: 2025/03/01 08:11:46 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/* checks if str[0] is '<' or '<<' , returns result */
void	assign_datatype_infile(char *str, unsigned char *datatype, int *i)
{
	if (str[0] == '<' && str[1] == '<')
		datatype[(*i)++] = HEREDOC;
	else if (str[0] == '<' && str[1] != '<')
		datatype[(*i)++] = INFILE;
}

/* scans input and assigns datatype according to operator sign */
void	assign_datatype(unsigned char *datatype, char **res, char **infile)
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

	x = -1;
	i = 0;
	/* _____________get infile_____________ */
	/* if infile[1], travel to the last infile '<' */
	cmd_tail = search_rstr(res[0], '<', ft_strlen(res[0]));
	if (infile[1])
		assign_datatype_infile(cmd_tail, datatype, &i);
	else if (!infile[1] && cmd_tail[0] == '<')
		assign_datatype_infile(cmd_tail, datatype, &i);
	/* get the rest */
	while (res[++x])
	{
		/* skip spaces & infile symbol */
		cmd_tail = skip_spaces(res[x], "< \t\n\v\f\r");
		cmd_tail = skip_if_symbol(cmd_tail, res[x][0], '<');
		cmd_tail = skip_spaces(cmd_tail, " \t\n\v\f\r");
		// if (!cmd_tail)
			// break ;
		/* get cmd_line + outfile */
		/*debug*/printf("assign_datatype=%s\n", cmd_tail);
		outfile = ft_split_shell(cmd_tail, ">");
		if (!outfile)
		{
			/*debug*/printf("****datatype NULL!\n");
			break ;
		}

		/*--------------extract_cmd_tail--------------*/
		/* if splittable */
		if (outfile[1] && (cmd_tail[0] != '>' || \
			(cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r"))))
		{
			datatype[i++] = WORD;
		}
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
			if (cmd_tail[0] == '>' && has_more_str_all(outfile, " \t\n\v\f\r")) //&& cmd_tail[1] != '>'
				datatype[i++] = WORD;
			else if (cmd_tail[0] && cmd_tail[0] != '>')
				datatype[i++] = WORD;
		}
		/*--------------extract outfiles--------------*/
		/* use ft_strchr */
		/* > out1 cmd */
		/* > out1 > out2 cmd */
		/* cmd > out1 > out2 */

		/* check the entire string */
		cmd_tail = res[x];
		while (cmd_tail && cmd_tail[0])
		{
			cmd_tail = ft_strchr(cmd_tail, '>');
			/*debug*/printf("datatype=%s\n", cmd_tail);
			if (!cmd_tail)
				break ;
			if (cmd_tail[1] == '>')
			{
				datatype[i++] = OUTFILE_A;
				cmd_tail++;
			}
			else if (cmd_tail[0] == '>')
				datatype[i++] = OUTFILE;
			cmd_tail++;
		}
		/* if splittable */
		/* if not splittable */

		/*--------------extract pipes--------------*/
		if (res[x + 1])
			datatype[i++] = PIPE;
		free_chr_ptr((void **)outfile);
	}
}

// void	assign_datatype(t_token *lst, char **res)
// {
// 	int	x;
// 	int	i;

// 	x = 0;
// 	i = 0;
// 	identify_op(res[i], &lst->datatype[x++]);
// 	while (res[i])
// 	{
// 		while (res[i])// && !is_target("<>|", res[i][0]))
// 		{
// 			if (is_target("<>|", res[i][0]) && res[i][1] == '\0')
// 				break ;
// 			i++;
// 		}
// 		if (res[i])
// 			identify_op(res[i++], &lst->datatype[x++]);
// 		else
// 			lst->datatype[x] = END;
// 	}
// }