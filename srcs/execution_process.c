/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:55 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/23 19:30:01 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	ft_execution(t_ms *data, char *cmd, char **cmd_args)
{
	char	*cmd_path;

	if (is_built_in(cmd))
	{
		if (execute_built_in(data, cmd_args))
			ms_free_all(data, -1, 0);
		else
			ms_free_all(data, -1, 1);
	}
	cmd_path = ft_cmdpath(cmd_args, data->exec.path);
	if (cmd_path == NULL)
	{
		ft_putstr_fd("./minishell: ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		ms_free_all(data, -1, 127);
	}
	if (execve(cmd_path, cmd_args, data->exec.envp) == -1)
	{
		ft_putstr_fd("./minishell: execve() error!\n", 2);
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
	if (ft_isempty(data->exec.cmd_args[index][0]) == 0)
		ft_execution(data, data->exec.cmd_args[index][0], \
data->exec.cmd_args[index]);
	ms_free_all(data, -1, 0);
}
