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

int	ft_isspace(char c)
{

	if (c == 32 || (c >= 9 && c <= 13))
			return (0);
	return (1);
}

int	ft_isEmpty(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	lst_cmd_count(t_token *lst)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i++] == WORD)
			size++;
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
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == WORD)
			cmd[j++] = ft_strdup(lst->data[i]);
		// if (lst->datatype[i] == PIPE)
		// 	if (cmd[j] == NULL)
		// 		cmd[j++] = ft_strdup("\0");
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

void	ft_process(t_ms *data, char **envp)
{
	pid_t	pid;
	int		p_status;
	int		i;

	p_status = 0;
	i = 0;
	while (i < data->exec.pipe_count * 2)
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
	block_signal(SIGINT);
	block_signal(SIGQUIT);
	while (wait(&p_status) >= 0)
	{
		if (WIFEXITED(p_status))
			data->exec.exit_code = WEXITSTATUS(p_status);
	}
	unblock_signal(SIGINT);
	unblock_signal(SIGQUIT);
}

void	ft_execs_init(t_ms *data, t_token *lst)
{
	char	**envp;
	char	**cmd;

	cmd = ft_cmd_init(data, lst);
	if (cmd == NULL)
	{
		printf("-minishell: command allocation fail!: Critical Error!\n");
		ms_free_all(data, 1); //cmd allocation fail exit minishell program free everything
	}
	envp = ft_envp(&data->env_var);
	if (envp == NULL)
	{
		free_chr_ptr((void **) cmd);
		printf("-minishell: environment allocation fail!: Critical Error!\n");
		ms_free_all(data, 1); //envp allocation fail exit minishell program free everything
	}
	// /*debug*/printf("___ft_execs_init___\n");
	// /*debug*/debug_print(cmd);

	/* execute only if there is cmd */
	data->exec.path = ft_get_path(envp);
	if (data->exec.path == NULL)
	{
		free_chr_ptr((void **) cmd);
		free_chr_ptr((void **) envp);
		printf("-minishell: environment path allocation fail!: Critical Error!\n");
		ms_free_all(data, 1); //get path fail, exit minishell program free everything
	}
	data->exec.cmd_args = ft_split_cmd(&data->exec, cmd);
	if (data->exec.cmd_args == NULL)
	{
		free_chr_ptr((void **) cmd);
		free_chr_ptr((void **) envp);
		printf("-minishell: split 3 dimensional command array allocation fail!: Critical Error!\n");
		ms_free_all(data, 1);  //split 3d cmd fail, exit minishell program free everything
	}
	free_chr_ptr((void **) cmd);
	// //free_chr_ptr((void **) cmd);
	ft_process(data, envp);
	free_chr_ptr((void **) envp);
}
