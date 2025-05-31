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
 * child function of process_cmd_tail
 * allocates enough space to store cmd and copies it
 * str = the entire line of cmd/pipeline before splitted by outfile '>'
 * uses malloc
 */
void	extract_cmd_tail(char **lst_data, int *i, char **outfile)
{
	char	**infile_check;
	int		start;
	char	*cmd_tail;

	start = 0;
	cmd_tail = outfile[0];
	if (!allocate_cmd_tail(&lst_data[*i], outfile, cmd_tail))
		return ;
	infile_check = ft_split_shell(cmd_tail, "<");
	start = ft_strlcpy(lst_data[(*i)], infile_check[0], \
ft_strlen(infile_check[0]) + 1);
	copy_cmd_tail(&lst_data[(*i)], &start, &infile_check[1]);
	free_chr_ptr((void **)infile_check);
	if (outfile[1])
		copy_cmd_tail(&lst_data[(*i)], &start, &outfile[1]);
	*i += 1;
}

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

	cmd_tail = skip_redirs(cmd_tail);
	if (!cmd_tail || !cmd_tail[0])
		return ;
	outfile = ft_split_shell(cmd_tail, ">");
	if (!outfile || !outfile[0])
		return ;
	extract_cmd_tail(lst_data, i, outfile);
	free_chr_ptr((void **)outfile);
}

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
		cmd_tail = skip_spaces(res[x], " \t\n\v\f\r");
		if (ft_strchr(cmd_tail, '<'))
			extract_infile(lst->data, &i, cmd_tail);
		process_cmd_tail(lst->data, &i, cmd_tail);
		process_outfile(lst->data, &i, cmd_tail);
		if (res[x + 1])
			extract_outfile(&lst->data[i++], "|");
	}
}

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
	res = ft_split_shell(str, "|");
	if (!res)
		return (0);
	count = get_malloc_size(res);
	if (!init_token_list(lst, (count + 1)))
		return (0);
	process_cmd(lst, res);
	cmd_expansion(lst->data, vars, exit_status);
	assign_datatype(lst->datatype, res);
	free_chr_ptr((void **)res);
	return (1);
}
