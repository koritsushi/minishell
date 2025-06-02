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
