/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:39:33 by mliyuan           #+#    #+#             */
/*   Updated: 2025/06/02 19:41:41 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

int	env_print(t_env **lst)
{
	t_env	*iter;

	iter = *lst;
	while (iter != NULL)
	{
		if (iter->exported == 2)
			printf("%s=%s\n", iter->env, iter->content);
		iter = iter->next;
	}
	return (0);
}

/* print out export env from minishell */
int	export_print(t_env **lst)
{
	t_env	*iter;
	char	*export_str;

	iter = *lst;
	export_str = "declare -x";
	while (iter != NULL)
	{
		if (iter->exported == 1)
			printf("%s %s\n", export_str, iter->env);
		if (iter->exported == 2)
			printf("%s %s=\"%s\"\n", export_str, iter->env, iter->content);
		iter = iter->next;
	}
	return (0);
}
