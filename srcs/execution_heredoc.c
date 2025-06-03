/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:17:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/06/03 14:27:34 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

extern int	g_signal;

void	infile_parsing_init(t_ms *data, t_token *lst)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == PIPE)
		{
			flag = 0;
			j++;
		}
		if ((lst->datatype[i] == INFILE || lst->datatype[i] == HEREDOC) && \
data->exec.infile_fd[j] > 2)
			close(data->exec.infile_fd[j]);
		if (lst->datatype[i] == INFILE)
			ft_infile_init(data, &data->exec.infile_fd[j], lst->data[i], &flag);
		else if (lst->datatype[i] == HEREDOC)
			ft_heredoc_init(data, lst->data[i], j);
		i++;
	}
}

void	outfile_parsing_init(t_ms *data, t_token *lst)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == PIPE)
		{
			flag = 0;
			j++;
		}
		if (lst->datatype[i] == OUTFILE || lst->datatype[i] == OUTFILE_A)
			if (data->exec.outfile_fd[j] > 2)
				close(data->exec.outfile_fd[j]);
		if (lst->datatype[i] == OUTFILE)
			data->exec.outfile_fd[j] = \
open(lst->data[i], O_RDWR | O_CREAT | O_TRUNC, 0664);
		else if (lst->datatype[i] == OUTFILE_A)
			data->exec.outfile_fd[j] = \
open(lst->data[i], O_RDWR | O_CREAT | O_APPEND, 0664);
		if (data->exec.outfile_fd[j] == -1)
			ft_outfile_init\
(data, &data->exec.outfile_fd[j], lst->data[i], &flag);
		i++;
	}
}
