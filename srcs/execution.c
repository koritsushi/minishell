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

char	**ft_cmd_init(t_ms *data, t_token *lst)
{
	int		i;
	int		j;
	int		size;
	char	**cmd;

	i = 0;
	j = 0;
	data->exec.cmd_count = lst_cmd_count(lst);
	size = data->exec.cmd_count;
	cmd = malloc(sizeof(char **) * (size + 1));
	if (cmd == NULL)
		return (NULL);
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == WORD)
			cmd[j++] = ft_strdup(lst->data[i]);
		i++;
	}
	cmd[j] = NULL;
	return (cmd);
}

void	ft_init_pipe(t_ms *data, t_token *lst)
{
	int		pipe_count;
	int		pipe_index;
	int		pipe_fd[2];

	pipe_index = 0;
	data->exec.pipe_count = lst_pipe_count(lst);
	pipe_count = data->exec.pipe_count;
	while (pipe_index < pipe_count)
	{
		if (pipe(pipe_fd) == -1)
			ms_free_all(data, 6, 1);
		data->exec.pipes[pipe_index][READ] = pipe_fd[READ];
		data->exec.pipes[pipe_index][WRITE] = pipe_fd[WRITE];
		pipe_index++;
	}
}

void	ft_process(t_ms *data)
{
	pid_t	pid;
	int		p_status;
	int		i;

	p_status = 0;
	i = 0;
	set_signal_action(3);
	while (i < data->exec.cmd_count)
	{
		pid = fork();
		if (pid == -1)
			ms_free_all(data, 7, 1);
		if (pid == 0)
			ft_child_process(data, i);
		else
			ft_parent_process(data, i);
		i++;
	}
	set_signal_action(2);
	while (wait(&p_status) >= 0)
		if (WIFEXITED(p_status))
			data->exec.exit_code = WEXITSTATUS(p_status);
	set_signal_action(1);
}
