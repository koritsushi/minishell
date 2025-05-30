/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:17:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/30 00:08:37 by mliyuan          ###   ########.fr       */
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
	int				hdpstatus;
	int				parsing_pipe[2];
	pid_t			pid;

	status = pipe(parsing_pipe);
	if (status == -1)
		ms_free_all(data, 6, 1);
	pid = fork();
	if (pid == -1)
		ms_free_all(data, 7, 1);
	if (pid == 0)
		ft_here_doc(data, delimiter, parsing_pipe);
	else
		close(parsing_pipe[WRITE]);
	status = 0;
	hdpstatus = 0;
	if (wait(&status))
	{
		if (WIFEXITED(status))
			hdpstatus = WEXITSTATUS(status);
	}
	if (hdpstatus > 0)
		ms_free_all(data, 5, 1);
	data->exec.infile_fd[j] = parsing_pipe[READ];
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
			ft_infile_init(&data->exec.infile_fd[j], lst->data[i], &flag);
		else if (lst->datatype[i] == HEREDOC)
			ft_heredoc_init(data, lst->data[i], j);
		i++;
	}
}

void	outfile_parsing_init(t_ms *data, t_token *lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == PIPE)
			j++;
		if (lst->datatype[i] == OUTFILE || lst->datatype[i] == OUTFILE_A)
			if (data->exec.outfile_fd[j] > 2)
				close(data->exec.outfile_fd[j]);
		if (lst->datatype[i] == OUTFILE)
			data->exec.outfile_fd[j] = \
open(lst->data[i], O_RDWR | O_CREAT | O_TRUNC, 0774);
		else if (lst->datatype[i] == OUTFILE_A)
			data->exec.outfile_fd[j] = \
open(lst->data[i], O_RDWR | O_CREAT | O_APPEND, 0774);
		if (data->exec.outfile_fd[j] == -1)
			ms_free_all(data, 4, 1);
		i++;
	}
}
