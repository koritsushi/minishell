/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_parent_process_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:32:43 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/21 11:29:04 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	fp_process(t_ms *data, int index)
{
	if (data->exec.pipe_count > 0)
		close(data->exec.pipes[index][WRITE]);
	if (data->exec.infile_fd[index] != 0)
		close(data->exec.infile_fd[index]);
	if (data->exec.outfile_fd[index] != 1)
		close(data->exec.outfile_fd[index]);
}

void	lp_process(t_ms *data, int index)
{
	close(data->exec.pipes[index - 1][WRITE]);
	close(data->exec.pipes[index - 1][READ]);
	if (data->exec.infile_fd[index] != 0)
		close(data->exec.infile_fd[index]);
	if (data->exec.outfile_fd[index] != 1)
		close(data->exec.outfile_fd[index]);
}

void	mp_process(t_ms *data, int index)
{
	close(data->exec.pipes[index - 1][READ]);
	close(data->exec.pipes[index][WRITE]);
	if (data->exec.infile_fd[index] != 0)
		close(data->exec.infile_fd[index]);
	if (data->exec.outfile_fd[index] != 1)
		close(data->exec.outfile_fd[index]);
}
