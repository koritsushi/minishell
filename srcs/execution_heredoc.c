/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:17:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/06/02 22:02:23 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	ft_pipe_doc(char *final, int parsing_pipe[2])
{
	close(parsing_pipe[READ]);
	ft_putstr_fd(final, parsing_pipe[WRITE]);
	close(parsing_pipe[WRITE]);
}

void	ft_here_doc(t_ms *data, char *delimiter, int parsing_pipe[2])
{
	char	*res;
	char	*tmp;
	char	*final;

	final = ft_strdup("");
	while (1)
	{
		write(STDOUT_FILENO, "> ", 3);
		res = get_next_line(STDIN_FILENO);
		if (res == NULL || !ft_strncmp(res, delimiter, ft_strlen(delimiter)))
		{
			if (res != NULL)
				free(res);
			break ;
		}
		shell_var_expansion(&res, data->env_var, data->exec.exit_code);
		tmp = ft_strjoin(final, res);
		free(final);
		final = ft_strdup(tmp);
		free_multiple_ptr_single(res, tmp, NULL);
	}
	ft_pipe_doc(final, parsing_pipe);
	free(final);
	ms_free_all(data, -1, 0);
}

void	ft_heredoc_init(t_ms *data, char *delimiter, int j)
{
	int				status;
	int				parsing_pipe[2];
	pid_t			pid;

	if (pipe(parsing_pipe) == -1)
		ms_free_all(data, 6, 1);
	pid = fork();
	if (pid == -1)
		ms_free_all(data, 7, 1);
	if (pid == 0)
	{
		set_signal_action(4);
		ft_here_doc(data, delimiter, parsing_pipe);
	}
	else
		close(parsing_pipe[WRITE]);
	set_signal_action(2);
	status = 0;
	if (wait(&status))
		if (WIFEXITED(status))
			data->exec.exit_code = WEXITSTATUS(status);
	set_signal_action(1);
	if (data->exec.exit_code == 0)
		data->exec.infile_fd[j] = parsing_pipe[READ];
	else
		data->exec.infile_fd[j] = 0;
}

void	infile_parsing_init(t_ms *data, t_token *lst)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == PIPE)
		{
			flag = 0;
			j++;
		}
		if ((lst->datatype[i] == INFILE || lst->datatype[i] == HEREDOC) && \
data->exec.infile_fd[j] > 2)
			close(data->exec.infile_fd[j]);
		if (lst->datatype[i] == INFILE)
			ft_infile_init(data, &data->exec.infile_fd[j], lst->data[i], &flag);
		else if (lst->datatype[i] == HEREDOC)
			ft_heredoc_init(data, lst->data[i], j);
		i++;
	}
}

void	outfile_parsing_init(t_ms *data, t_token *lst)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == PIPE)
		{
			flag = 0;
			j++;
		}
		if (lst->datatype[i] == OUTFILE || lst->datatype[i] == OUTFILE_A)
			if (data->exec.outfile_fd[j] > 2)
				close(data->exec.outfile_fd[j]);
		if (lst->datatype[i] == OUTFILE)
			data->exec.outfile_fd[j] = \
open(lst->data[i], O_RDWR | O_CREAT | O_TRUNC, 0664);
		else if (lst->datatype[i] == OUTFILE_A)
			data->exec.outfile_fd[j] = \
open(lst->data[i], O_RDWR | O_CREAT | O_APPEND, 0664);
		if (data->exec.outfile_fd[j] == -1)
			ft_outfile_init\
(data, &data->exec.outfile_fd[j], lst->data[i], &flag);
		i++;
	}
}
