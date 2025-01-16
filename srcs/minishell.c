/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:12:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/16 16:07:22 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	if (argc > 1 && ft_strncmp(argv[0], "minishell", 9) != 0)
		exit(127);
	set_signal_action();
	block_signal(SIGQUIT);
	while (1)
	{
		text = readline("\033[34mminishell> \033[0m");
		if (text == NULL)
			exit(ENOMEM);
		if (ft_strncmp(text, "exit", 4) == 0)
		{
			free(text);
			ft_putstr_fd("\033[32mminishell exited!\033[0m\n", 1);
			break ;
		}
		ft_putstr_fd(text, 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
