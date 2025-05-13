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

int	lst_cmd_count(t_token *lst)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == WORD)
			size++;
		i++;
	}
	return (size);
}

int	lst_pipe_count(t_token *lst)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == PIPE)
			size++;
		i++;
	}
	return (size);
}

char	**ft_cmd_init(t_token *lst)
{
	int		i;
	int		j;
	int		size;
	char	**cmd;

	i = 0;
	j = 0;
	size = lst_cmd_count(lst);
	cmd = malloc(sizeof(char **) * (size + 1));
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
	int		i;

	pipe_count = 0;
	i = -1;
	while (lst->data[++i] != NULL)
	{
		if (lst->datatype[i] == PIPE)
			pipe_count += 1;
	}
	data->exec.cmd_count = pipe_count * 2;
	pipe_index = 0;
	while (pipe_index < pipe_count)
	{
		if (pipe(pipe_fd) == -1)
		{
			printf("\033[34mminishell: pipe() error!\033[0m\n");
			/*free & exit function here*/ 
			exit(1);
		}
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
			/*free & exit function here*/ 
			exit(1);
		}
		if (pid == 0)
			ft_child_process(data, i, envp);
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

void	ft_execs_init(t_ms *data, t_token *lst)
{
	char	**envp;
	char	**cmd;

	ft_init_pipe(data, lst);
	cmd = ft_cmd_init(lst);
	envp = ft_envp(&data->env_var);
	data->exec.path = ft_get_path(envp);
	data->exec.cmd_args = ft_split_cmd(&data->exec, cmd);
	//free_chr_ptr((void **) cmd);
	ft_process(data, envp);
}