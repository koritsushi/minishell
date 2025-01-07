/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:12:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/07 16:24:09 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	char	*text;

	if (argc > 1 && ft_strncmp(argv[1], "minishell", 9) != 0)
	{
		exit(-1);
	}
	while (1)
	{
		write(1, "minishell>", 10);
		text = get_next_line(0);
		if (text == NULL)
		{
			break ;
		}
		ft_putstr_fd(text, 1);
		if (ft_strncmp(text, "exit", 4) == 0)
		{
			free(text);
			ft_putstr_fd("minishell exited!\n", 1);
			break ;
		}
	}
	return (0);
}
