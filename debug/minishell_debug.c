/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:57:05 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/25 15:58:48 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main (int argc, char **argv, char **env)
{
	t_ms data;

	msh_init(&data, env);
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
}