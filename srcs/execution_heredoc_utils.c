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

void	ft_infile_init(int *infile_fd, char *data, int *flag)
{
	*infile_fd = open(data, O_RDONLY);
	if (*infile_fd == -1)
	{
		*infile_fd = open("/dev/null", O_RDONLY);
		if (*flag == 0)
		{
			printf("-minishell: %s: %s\n", data, strerror(errno));
			*flag = 1;
		}
	}
}
