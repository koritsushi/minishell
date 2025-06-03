/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:10:14 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/29 23:10:14 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

extern int	g_signal;

void	ft_infile_init(t_ms *data, int *infile_fd, char *infile, int *flag)
{
	char	*error;

	*infile_fd = open(infile, O_RDONLY);
	data->exec.exit_code = 0;
	if (*infile_fd == -1)
	{
		*infile_fd = open("/dev/null", O_RDONLY);
		if (*flag == 0)
		{
			error = ft_strjoin("-minishell: ", infile);
			perror(error);
			free(error);
			*flag = 1;
			data->exec.exit_code = 1;
		}
	}
}

void	ft_outfile_init(t_ms *data, int *outfile_fd, char *outfile, int *flag)
{
	char	*error;

	*outfile_fd = open("/dev/null", O_WRONLY);
	data->exec.exit_code = 0;
	if (*flag == 0)
	{
		error = ft_strjoin("-minishell: ", outfile);
		perror(error);
		free(error);
		*flag = 1;
		data->exec.exit_code = 1;
	}
}

/*
 * child function in ft_here_doc
 * checks if res matches delimiter,
 * if true, free res
 */
static int	match_delimiter(char **res, char *del)
{
	char	*str;

	str = *res;
	if (str == NULL || (!ft_strcmp(str, del)))
	{
		if (str != NULL)
			free(str);
		return (1);
	}
	return (0);
}

int	g_signal_130(int *status)
{
	if (g_signal == 130)
	{
		*status = 130;
		return (1);
	}
	return (0);
}

int	retrieve_here_doc(t_ms *data, char *del, int flag_quote, char **final)
{
	char	*res;
	char	*tmp;
	char	*tmp_del;
	int		status;

	status = 0;
	tmp_del = ft_strdup(del);
	quote_removal(&tmp_del);
	while (1)
	{
		res = readline("> ");
		if (g_signal_130(&status))
			break ;
		if (match_delimiter(&res, tmp_del))
			break ;
		if (!flag_quote)
			shell_var_expansion(&res, data->env_var, data->exec.exit_code);
		tmp = ft_strjoin(*final, res);
		free(*final);
		*final = ft_strjoin(tmp, "\n");
		free_multiple_ptr_single(res, tmp, NULL);
	}
	free(tmp_del);
	return (status);
}
