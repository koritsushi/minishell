/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:55 by mliyuan           #+#    #+#             */
/*   Updated: 2025/06/02 15:25:01 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static void	ft_process_built_in(t_ms *data, char *cmd, char **cmd_args)
{
	if (is_built_in(cmd))
	{
		if (execute_built_in(data, cmd_args))
			ms_free_all(data, -1, 0);
		else
			ms_free_all(data, -1, 1);
	}
}

void	ft_execution(t_ms *data, char *cmd, char **cmd_args)
{
	char	*cmd_path;
	char	*err;

	ft_process_built_in(data, cmd, cmd_args);
	if (ft_strncmp(cmd_args[0], "../", 3) != 0 && \
ft_strncmp(cmd_args[0], "./", 2) != 0 && \
ft_strncmp(cmd_args[0], "/", 1) != 0 && \
ft_strncmp(cmd_args[0], ".", 1) != 0)
		cmd_path = ft_absolute_path(cmd_args, data->exec.path);
	else
		cmd_path = ft_relative_path(cmd_args[0]);
	if (cmd_path == NULL)
	{
		err = ft_strjoin("-minishell: ", cmd_args[0]);
		perror(err);
		free(err);
		ms_free_all(data, -1, 127);
	}
	if (execve(cmd_path, cmd_args, data->exec.envp) == -1)
	{
		perror("-minishell: execve() error!");
		free(cmd_path);
		ms_free_all(data, -1, -1);
	}
}

void	close_pipe(t_ms *data, int index)
{
	index = index + 1;
	while (index < data->exec.pipe_count)
	{
		close(data->exec.pipes[index][READ]);
		close(data->exec.pipes[index][WRITE]);
		index++;
	}
}

void	ft_parent_process(t_ms *data, int index)
{
	if (index == 0)
		fp_process(data, index);
	else if (index == data->exec.cmd_count - 1)
		lp_process(data, index);
	else
		mp_process(data, index);
}

void	ft_child_process(t_ms *data, int index)
{
	if (index == 0)
		fc_process(data, index);
	else if (index == data->exec.cmd_count - 1)
		lc_process(data, index);
	else
		mc_process(data, index);
	if (ft_isempty2(data->exec.cmd_args[index][0]) == 0)
		ft_execution(data, data->exec.cmd_args[index][0], \
data->exec.cmd_args[index]);
	ms_free_all(data, -1, 0);
}
