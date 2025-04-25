/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:39:33 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/25 16:40:08 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

void	env_print(t_env **lst)
{
	t_env	*iter;

	iter = *lst;
	while (iter != NULL)
	{
		if (iter->content != NULL && iter->exported == 1)
			printf("%s=%s\n", iter->env, iter->content);
		iter = iter->next;
	}
}

//print out export env from minishell 
void	export_print(t_env **lst)
{
	t_env	*iter;
	char	*export_str;

	iter = *lst;
	export_str = "declare -x";
	while (iter != NULL)
	{
		if (iter->content != NULL && iter->exported == 1)
			printf("%s %s=%s\n", export_str, iter->env, iter->content);
		iter = iter->next;
	}
}