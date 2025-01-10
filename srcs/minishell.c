/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:12:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/09 23:33:50 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile int g_unblock_sigquit = 0;

int	ft_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		if (str[i] > 32)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	char	*text;

	if (argc > 1 && ft_strncmp(argv[1], "minishell", 9) != 0)
		exit(127);
	set_signal_action();
	block_signal(SIGQUIT);
	while (1)
	{
		ft_putstr_fd("\033[34mminishell> \033[0m", 1);
		text = get_next_line(0);
		if (text == NULL)
			exit(ENOMEM);
		if (ft_strncmp(text, "exit", 4) == 0)
		{
			free(text);
			ft_putstr_fd("\033[32mminishell exited!\033[0m\n", 1);
			break ;
		}
		if (ft_isspace(text) == 0)
		{
			ft_putstr_fd(text, 1);
			ft_putstr_fd("\n", 1);
		}
	}
	return (0);
}
