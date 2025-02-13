/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:12:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/02/12 18:48:38 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	// t_token	lst;

	if (argc > 1 && ft_strncmp(argv[0], "minishell", 9) != 0)
		exit(127);
	set_signal_action();
	block_signal(SIGQUIT);
	while (1)
	{
		text = readline("\033[34mminishell ˚𓆝 ⋆｡𓆟 ⋆｡𓆞˚ 𓇼  > \033[0m");
		if (text == NULL)
			exit(ENOMEM);
		if (*text)
			add_history(text);
		if (ft_strncmp(text, "exit", 4) == 0)
		{
			free(text);
			ft_putstr_fd("\033[32mminishell exited!\033[0m\n", 1);
			break ;
		}
		/*get_cmd_line*/
		// get_cmd_line(text, &lst);
		// ft_putstr_fd(text, 1);
		// ft_putstr_fd("\n", 1);
		free(text);
		// free_all(&lst);
	}
	return (0);
}

