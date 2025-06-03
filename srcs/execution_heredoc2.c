/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:24:54 by hsim              #+#    #+#             */
/*   Updated: 2025/06/03 14:29:01 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	ft_pipe_doc(char *final, int parsing_pipe[2])
{
	close(parsing_pipe[READ]);
	ft_putstr_fd(final, parsing_pipe[WRITE]);
	close(parsing_pipe[WRITE]);
}

void	ft_here_doc(t_ms *data, char *deli, int parsing_pipe[2])
{
	char	*final;
	int		flag_quote;
	int		status;

	status = 0;
	final = ft_strdup("");
	flag_quote = 0;
	if (deli && (is_target(deli, '\'') || is_target(deli, '\"')))
		flag_quote = 1;
	status = retrieve_here_doc(data, deli, flag_quote, &final);
	ft_pipe_doc(final, parsing_pipe);
	free(final);
	ms_free_all(data, -1, status);
}

/* child function to ft_heredoc_init to shorten function line */
static void	handle_heredoc(t_ms *data, char *delimiter, int parsing_pipe[2])
{
	set_signal_action(4);
	ft_here_doc(data, delimiter, parsing_pipe);
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
		handle_heredoc(data, delimiter, parsing_pipe);
	else
		close(parsing_pipe[WRITE]);
	set_signal_action(2);
	status = 0;
	if (wait(&status))
		if (WIFEXITED(status))
			data->exec.exit_code = WEXITSTATUS(status);
	if (data->exec.exit_code == 0)
		data->exec.infile_fd[j] = parsing_pipe[READ];
	else
		data->exec.infile_fd[j] = open("/dev/null", O_RDONLY);
	set_signal_action(1);
}
