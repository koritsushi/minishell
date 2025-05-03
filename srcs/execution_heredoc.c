/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:17:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/03 21:55:11 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*ft_heredoc(char *delimiter)
{
	char	*res;
	char	*tmp;
	char	*final;
	
	while (1)
	{
		write(STDOUT_FILENO, "> ", 3);
		res = get_next_line(STDIN_FILENO);
		if (res == NULL || ft_strncmp(res, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(res);
			break;
		}
		tmp = ft_strjoin(res, "\n");
		final = ft_strjoin(final, res);
		free(res);
		free(tmp);
	}
	return (final);
}