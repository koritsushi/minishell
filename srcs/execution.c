/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:20:34 by mliyuan           #+#    #+#             */
/*   Updated: 2025/02/18 17:20:34 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/*
int access() function to check in fork child of execution
instead of checking and parsing before execution

execve() can run executable of compile programs of builtins

so question here is that do we run builins within minishell
or execve it like cmds but recognize it as local lib

ans: fork out a child process just for builtin function for 
them to be able redirec in/out for shell commands function
*/
void	ft_init_pipe(t_ms *data, int argc)
{
	int		pipe_count;
	int		pipe_index;
	int		pipe_fd[2];

	data->exec.cmd_count = argc - 3;
	pipe_count = data->exec.cmd_count - 1;
	// if (data->exec.here_doc == 1)
	// 	pipe_count += 1;
	pipe_index = 0;
	while (pipe_index < pipe_count)
	{
		if (pipe(pipe_fd) == -1)
			printf("\033[34mminishell: pipe() error!\033[0m\n");
		data->exec.pipes[pipe_index][READ] = pipe_fd[READ];
		data->exec.pipes[pipe_index][WRITE] = pipe_fd[WRITE];
		pipe_index++;
	}
}


static void	ft_process(t_ms *data, char **envp)
{
	pid_t	pid;
	int		p_status;
	int		i;

	p_status = 0;
	i = 0;
	while (i < data->exec.cmd_count)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("\033[34mminishell: fork() error!\033[0m\n");
			exit(1);
		}
		if (pid == 0)
			ft_child_process(data, i);
		else
			ft_parent_process(data, i);
		i++;
	}
	while (wait(&p_status) >= 0)
	{
		if (WIFEXITED(p_status))
			data->exec.exit_code = WEXITSTATUS(p_status);
	}
}