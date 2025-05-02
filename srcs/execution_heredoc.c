/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:17:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/02 18:17:39 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	ft_heredoc(char *delimiter)
{
	char	*res;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 10);
		res = get_next_line(STDIN_FILENO);
		if (res == NULL)
			return (free(res));
		else if (ft_strncmp(res, delimiter, ft_strlen(delimiter)) == 0)
			return (free(res));
		ft_putstr_fd(res, 1);
		free(res);
	}
}