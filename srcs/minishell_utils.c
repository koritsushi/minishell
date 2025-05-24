/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:27:23 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/23 16:49:28 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * child function in execute_functions
 * checks if entire cmd_line has pipes
 */
int	has_pipes(t_token lst)
{
	int	i;

	i = 0;
	while (lst.data[i])
	{
		if (lst.datatype[i] == PIPE)
			return (1);
		i++;
	}
	return (0);
}

int	has_infile_outfile(t_token lst)
{
	int	i;

	i = 0;
	while (lst.data[i])
	{
		if (lst.datatype[i] == INFILE || lst.datatype[i] == HEREDOC)
			return (1);
		if (lst.datatype[i] == OUTFILE || lst.datatype[i] == OUTFILE_A)
			return (1);
		i++;
	}
	return (0);
}
