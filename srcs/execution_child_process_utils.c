/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child_process_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:33:47 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/31 20:21:46 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	fc_process(t_ms *data, int index)
{
	if (data->exec.pipe_count > 0)
		close(data->exec.pipes[index][READ]);
	if (data->exec.infile_fd[index] > 2)
	{
		dup2(data->exec.infile_fd[index], STDIN_FILENO);
		close(data->exec.infile_fd[index]);
	}
	if (data->exec.pipe_count > 0)
	{
		dup2(data->exec.pipes[index][WRITE], STDOUT_FILENO);
		close(data->exec.pipes[index][WRITE]);
		close_pipe(data, index);
	}
	if (data->exec.outfile_fd[index] > 2)
	{
		dup2(data->exec.outfile_fd[index], STDOUT_FILENO);
		close(data->exec.outfile_fd[index]);
	}
}

void	lc_process(t_ms *data, int index)
{
	close(data->exec.pipes[index - 1][WRITE]);
	dup2(data->exec.pipes[index - 1][READ], STDIN_FILENO);
	if (data->exec.infile_fd[index] > 2)
	{
		dup2(data->exec.infile_fd[index], STDIN_FILENO);
		close(data->exec.infile_fd[index]);
	}
	close(data->exec.pipes[index - 1][READ]);
	if (data->exec.outfile_fd[index] > 2)
	{
		dup2(data->exec.outfile_fd[index], STDOUT_FILENO);
		close(data->exec.outfile_fd[index]);
	}
}

void	mc_process(t_ms *data, int index)
{
	close(data->exec.pipes[index - 1][WRITE]);
	dup2(data->exec.pipes[index - 1][READ], STDIN_FILENO);
	if (data->exec.infile_fd[index] > 2)
	{
		dup2(data->exec.infile_fd[index], STDIN_FILENO);
		close(data->exec.infile_fd[index]);
	}
	close(data->exec.pipes[index][READ]);
	dup2(data->exec.pipes[index][WRITE], STDOUT_FILENO);
	close(data->exec.pipes[index][WRITE]);
	close_pipe(data, index);
	if (data->exec.outfile_fd[index] > 2)
	{
		dup2(data->exec.outfile_fd[index], STDOUT_FILENO);
		close(data->exec.outfile_fd[index]);
	}
}
