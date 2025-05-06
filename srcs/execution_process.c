/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:55 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/06 16:35:16 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/execution.h"

int	execution(t_ms *data, char *cmd_paths, char **cmd_args, char **envp)
{
	if (execve(cmd_paths, cmd_args, envp) == -1)
	{
		printf("./pipex: execve() error!\n");
		exit(1);
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

void	ft_child_process(t_exec *exec, int index)
{
	if (index == 0)
		f_process(exec, index);
	else if (index == exec->cmd_count - 1)
		l_process(exec, index);
	else
		m_process(exec, index);
	ft_execute(exec, exec->cmd_paths[index], exec->cmd_args[index], exec->envp);
}