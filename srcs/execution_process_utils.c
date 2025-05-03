/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:16:21 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/03 13:58:09 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	f_process(t_exec *data, int index)
{
	close(data->pipes[index][READ]);
	dup2(data->infile_fd, STDIN_FILENO);
	dup2(data->pipes[index][WRITE], STDOUT_FILENO);
	close(data->pipes[index][WRITE]);
	close(data->infile_fd);
	close_pipe(data, index);
}

void	l_process(t_exec *data, int index)
{
	close(data->pipes[index - 1][WRITE]);
	dup2(data->pipes[index - 1][READ], STDIN_FILENO);
	dup2(data->outfile_fd, STDOUT_FILENO);
	close(data->pipes[index - 1][READ]);
	close(data->outfile_fd);
}

void	m_process(t_exec *data, int index)
{
	close(data->pipes[index - 1][WRITE]);
	dup2(data->pipes[index - 1][READ], STDIN_FILENO);
	dup2(data->pipes[index][WRITE], STDOUT_FILENO);
	close(data->pipes[index][WRITE]);
	close(data->pipes[index][READ]);
	close_pipe(data, index);
}