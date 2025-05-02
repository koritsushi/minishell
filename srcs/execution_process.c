/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:55 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/02 18:16:01 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/execution.h"

void	ft_parent_process(t_exec *data, int index)
{
	if (index == 0)
	{
		close(data->pipes[index][WRITE]);
		close(data->infile_fd);
	}
	else if (index == data->cmd_count - 1)
	{
		close(data->pipes[index - 1][WRITE]);
		close(data->pipes[index - 1][READ]);
		close(data->outfile_fd);
	}
	else
	{
		close(data->pipes[index - 1][READ]);
		close(data->pipes[index][WRITE]);
	}
}

void	close_pipe(t_exec *data, int index)
{
	index = index + 1;
	while (index < data->cmd_count - 1)
	{
		close(data->pipes[index][READ]);
		close(data->pipes[index][WRITE]);
		index++;
	}
}

void	ft_child_process(t_exec *data, int index)
{
	if (index == 0)
	{
		f_process(data, index);
		close_pipe(data, index);
	}
	else if (index == data->cmd_count - 1)
	{
		l_process(data, index);
	}
	else
	{
		m_process(data, index);
		close_pipe(data, index);
	}
}