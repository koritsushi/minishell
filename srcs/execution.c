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

void	ft_cmd_init(t_exec *exec, char *data)
{
	int		i;
	int		size;
	char	**str;

	i = 0;
	size = 0;
	if (exec->cmd_args == NULL)
	{
		exec->cmd_args = malloc(sizeof(char **) * (1 + 1));
	}
	else
	{
		size = ft_arr_len(exec->cmd_args) + 1;
		str = malloc(sizeof(char **) * (size));
		while (exec->cmd_args[i] != NULL)
		{
			str[i] = exec->cmd_args[i];
			i++;
		}
	}
	str[i++] = ft_strdup(data);
	str[i] = NULL;
}

void	ft_infile_init(t_exec *exec, t_token *lst)
{
	int	i;
	int	infile;

	i = 0;
	infile = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == INFILE && exec->infile_fd[infile] == 0)
			exec->infile_fd[infile] = open(lst->data[i], O_RDONLY);
		if (lst->datatype[i] == PIPE)
			infile++;
		i++;
	}
}

void	ft_heredoc_init(t_exec *exec, t_token *lst)
{

}

void 	ft_outfile_init(t_exec *exec, t_token *lst)
{

}

void	ft_outfileA_init(t_exec *exec, t_token *lst)
{

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

void	ft_execs_init(t_ms *data, t_token *lst)
{
	ft_init_pipe(data, lst);
	ft_infile_init(data, lst);
	ft_outfile_init(data, lst);
	ft_outfileA_init(data, lst);
	
	ft_process(data, envp);
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