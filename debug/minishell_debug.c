/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:57:05 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/25 18:50:05 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main (int argc, char **argv, char **env)
{
	t_ms data;
	//t_ms data2;
	
	data.env_var = NULL;
	//data2.env_var = NULL;
	msh_init(&data, env);
	// t_env *tmp = data.env_var;
	// printf("env address:%p\n", data.env_var);
	// while (tmp != NULL)
	// {
	// 	printf("name:%s, content:%s,", tmp->env, tmp->content);
	// 	printf("exported:%d\n", tmp->exported);
	// 	tmp = tmp->next;
	// }
	//unset(&data.env_var, data2.env_var);
	//export(&data.env_var, data2.env_var);
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

	if (argc > 1)
	{
		if (strcmp(argv[1], "echo") == 0)
		{
			ft_echo(argc, argv+1);
		}
		else if (strcmp(argv[1], "pwd") == 0)
		{
			ft_pwd();
		}	
		else if (strcmp(argv[1], "cd") == 0)
		{
			ft_pwd();
			ft_cd(&data.env_var, argv[2]);
			ft_pwd();
		}
		else if (strcmp(argv[1], "env") == 0)
		{
			env_print(&data.env_var);
		}
		else if (strcmp(argv[1], "export") == 0)
		{
			export_print(&data.env_var);
		}
		else if (strcmp(argv[1], "unset") == 0)
		{
			env_print(&data.env_var);
			t_env *tmp = ft_lstnew_shenv(argv[2], argv[2], 1);
			unset(&data.env_var, tmp);
			ft_lstdelone_env(tmp, free);
			printf("===========================\n");
			env_print(&data.env_var);
		}
	}
}