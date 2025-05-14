/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:17:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/14 16:22:46 by hsim             ###   ########.fr       */
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
		if (res == NULL)
			break ; //exit and free everything
		else if (ft_strncmp(res, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(res);
			break ;
		}
		shell_var_expansion(&res, data->env_var, data->exec.exit_code);
		// /*debug*/printf("ft_here_doc:exp:\033[93m%s\033[0m.\n", res);
		// tmp = ft_strjoin(res, "\n");
		tmp = ft_strjoin(final, res);
		free(final);
		final = ft_strdup(tmp);
		free_multiple_ptr_single(res, tmp, NULL);
	}
	if (data == NULL)
		return ;
	// /*debug*/printf("\033[100m___ft_here_doc___\033[0m\n\033[90m%s\033[0m", final);

	close(parsing_pipe[READ]);
	ft_putstr_fd(final, parsing_pipe[WRITE]);
	close(parsing_pipe[WRITE]);

	free(final);
	exit(0); //exit and free everything
}

void	ft_heredoc_init(t_ms *data, char *delimiter, int j)
{
	int				status;
	int				hdpstatus = 0;
	int				parsing_pipe[2];
	pid_t			pid;

	status = pipe(parsing_pipe);
	if (status == -1)
		exit(1);//pipe fail, free all structs and exit minishell
	pid = fork();
	if (pid == -1)
		exit(1);//fork fail, free all structs and exit minishell
	if (pid == 0)
	{
		/*debug*/printf("ft_heredoc_init:pid:%d\n", getpid());
		ft_here_doc(data, delimiter, parsing_pipe);
	}
	else
		close(parsing_pipe[WRITE]);
	status = 0;
	if (wait(&status))
	{
		if (WIFEXITED(status))
			hdpstatus = WEXITSTATUS(status);
	}
	if (hdpstatus > 0)
		exit(1);//child fail, free all structs and exit minishell
	data->exec.infile_fd[j] = parsing_pipe[READ];
	//leave parsing_pipe[0] open and only close after execve
}

void	infile_parsing_init(t_ms *data, t_token *lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == PIPE)
			j++;
		if (data->exec.infile_fd[j] > 2 && (lst->datatype[i] == INFILE || lst->datatype[i] == HEREDOC))
			close(data->exec.infile_fd[j]);
		if (lst->datatype[i] == INFILE)
		{
			data->exec.infile_fd[j] = open(lst->data[i], O_RDONLY);
			if (data->exec.infile_fd[j] == -1)
			{
				data->exec.infile_fd[j] = open("/dev/null", O_RDONLY);
				printf("-minishell: %s: %s\n", lst->data[i], strerror(errno)); //infile open fail, display error message
			}
		}
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
		if (lst->datatype[i] != PIPE)
			j++;
		if (data->exec.outfile_fd[j] > 2 && (lst->datatype[i] == OUTFILE || lst->datatype[i] == OUTFILE_A))
				close(data->exec.outfile_fd[j]);
		if (lst->datatype[i] == OUTFILE)		
			data->exec.outfile_fd[j] = \
open(lst->data[i], O_RDWR | O_CREAT | O_TRUNC, 0774);
		else if (lst->datatype[i] == OUTFILE_A)
			data->exec.outfile_fd[j] = \
open(lst->data[i], O_RDWR | O_CREAT | O_APPEND, 0774);
		if (data->exec.outfile_fd[j] == -1)
			exit(1); //open() create fail, free all structs and exit minishell
		i++;
	}
}
