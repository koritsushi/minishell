/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:17:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/07 22:22:47 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

// char	*ft_heredoc(char *delimiter)
// {
// 	char	*res;
// 	char	*tmp;
// 	char	*final;

// 	while (1)
// 	{
// 		write(STDOUT_FILENO, "> ", 3);
// 		res = get_next_line(STDIN_FILENO);
// 		if (res == NULL)
// 			break ;
// 		else if (ft_strncmp(res, delimiter, ft_strlen(delimiter)) == 0)
// 		{
// 			free(res);
// 			break ;
// 		}
// 		tmp = ft_strjoin(res, "\n");
// 		final = ft_strjoin(final, res);
// 		free(res);
// 		free(tmp);
// 	}
// 	return (final);
// }

void	ft_here_doc(char *delimiter)
{
	char	*res;
	char	*tmp;
	char	*final;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 3);
		res = get_next_line(STDIN_FILENO);
		if (res == NULL)
			exit_free();
		else if (ft_strncmp(res, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(res);
			break ;
		}
		tmp = ft_strjoin(res, "\n");
		final = ft_strjoin(final, res);
		free(res);
		free(tmp);
	}
	shell_var_expansion(final);
	close(parsing_pipe[READ]);
	ft_putstr_fd(final, parsing_pipe[WRITE]);
	free(final);
	exit_free();
}

void	ft_heredoc_init(char *delimiter, int j, int infile_fd)
{
	int				parsing_pipe[2];
	pid_t			pid;

	if (pipe(parsing_pipe) == -1)
		;//pipe fail, free all structs and exit minishell
	pid = fork();
	if (pid == -1)
		;//fork fail, free all structs and exit minishell
	if (pid == 0)
		ft_here_doc(delimiter);
	else
		close(parsing_pipe[1]);
	if (waitpid(&status))
	{
		if (WIFEXITED(status))
			heredocpstatus = WEXITSTATUS(p_status);
	}
	if (heredocpstatus > 0)
		;//child fail, free all structs and exit minishell
	infile_fd = parsing_pipe[0];
	//leave parsing_pipe[0] open and only close after execve
}

void	infile_parsing_init(t_exec *exec, t_token *lst)
{
	unsigned int	i;
	unsigned int	j;

	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == PIPE)
			j++;
		if (lst->datatype[i + 1] == INFILE || lst->datatype[i + 1] == HEREDOC)
		{
			if (exec->infile_fd[j] != 0)
				close(exec->infile_fd[j]);
		}
		if (lst->datatype[i] == INFILE)
			exec->infile_fd[j] = open(lst->data, RD_ONLY);
		if (exec->infile_fd[j] == -1)
			; //open fail, free all structs and exit minishell
		else if (lst->datatype[i] == HEREDOC)
			ft_heredoc(lst->data[i], j, exec->infile_fd[j]);
		i++;
	}
}

void	outfile_parsing_init(t_exec *exec, t_token *lst)
{
	unsigned int	i;
	unsigned int	j;

	while (lst->data[i] != NULL)
	{
		while (lst->data[i] && lst->datatype[i] != PIPE)
		{			
			if (i > 0 && exec->outfile_fd != 0)
					close(exec->outfile_fd[j]);
			if (lst->datatype[i] == OUTFILE)		
				exec->outfile_fd[j] = open(lst->data[i], O_RDWR | O_CREAT | O_TRUNC, 0774);
			else if (lst->datatype[i] == OUTFILE_A)
				exec->outfile_fd[j] = open(lst->data[i], O_RDWR | O_CREAT | O_APPEND, 0774);
			if (exec->outfile_fd[j] == -1)
				exit(1); //open() create fail, free all structs and exit minishell
			i++;
		}
		j++;
	}
}
