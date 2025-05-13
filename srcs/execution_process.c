/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:55 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/13 16:50:50 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/execution.h"

void	ft_execution(t_ms *data, char *cmd, char **cmd_args, char **envp)
{
	char *cmd_path;

	if (is_built_in(cmd))
	{
		if (execute_built_in(data, cmd_args))
			exit(0); //finish builtin function and free all struct in childProcess
		else
			exit(1); //exit and free all struct in childProcess
	}
	cmd_path = ft_cmdpath(cmd_args, data->exec.path);
	if (cmd_path == NULL)
		exit(1); //exit and free all struct in childProcess
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		printf("./minishell: execve() error!\n");
		exit(1); //exit and free all struct in childProcess with Minishell then exit minishell
	}
}

void	close_pipe(t_ms *data, int index)
{
	index = index + 1;
	while (index < data->exec.cmd_count - 1)
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

void	ft_child_process(t_ms *data, int index, char **envp)
{
	if (index == 0)
		fc_process(data, index);
	else if (index == data->exec.cmd_count - 1)
		lc_process(data, index);
	else
		mc_process(data, index);
	if (data->exec.cmd_args != NULL)
		ft_execution(data, data->exec.cmd_args[index][0], data->exec.cmd_args[index], envp);
}