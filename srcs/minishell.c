/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:12:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/24 20:32:35 by mliyuan          ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	t_ms	data;
	t_ms	data2;
	char	*text;

	if (argc > 1 && ft_strncmp(argv[0], "minishell", 9) != 0)
		exit(127);
	set_signal_action();
	//block_signal(SIGQUIT);
	//block_signal(SIGINT);
	data.env_var = NULL;
	data2.env_var = NULL;
	char **envstr_2 = ft_split("var=2 var=3", ' ');
	msh_init(&data, env);
	msh_init(&data2, envstr_2);
	
	//DEBUG
	// t_env *tmp = data.env_var;
	// printf("env address:%p\n", data.env_var);
	// while (tmp != NULL)
	// {
	// 	printf("name:%s, content:%s,", tmp->env, tmp->content);
	// 	printf("exported:%d\n", tmp->exported);
	// 	tmp = tmp->next;
	// }
	//unset(&data.env_var, data2.env_var);
	// export(&data.env_var, data2.env_var);
	//DEBUG
	// tmp = data.env_var;
	// printf("env address:%p\n", data.env_var);
	// while (tmp != NULL)
	// {
	// 	printf("name:%s, content:%s,", tmp->env, tmp->content);
	// 	printf("exported:%d\n", tmp->exported);
	// 	tmp = tmp->next;
	// }
	// t_env *tmp2 = data2.env_var;
	// printf("env address:%p\n", data2.env_var);
	// while (tmp2 != NULL)
	// {
	// 	printf("name:%s, content:%s,", tmp2->env, tmp2->content);
	// 	printf("exported:%d\n", tmp2->exported);
	// 	tmp2 = tmp2->next;
	// }
	while (1)
	{
		text = readline("\033[34mminishell> \033[0m");
		if (text == NULL)
		{
			ft_putstr_fd("\e[0;31mlogout\e[0;31m\n", 1);
			exit(ENOMEM);
		}
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
