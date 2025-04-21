/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:16:05 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/20 21:16:05 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

t_env	env_new(char **env, void *content)
{
	t_env *en;

	if (content == NULL)
		return (NULL);
	en = malloc(sizeof(t_env));
	if (e == NULL)
		return (NULL);
	en->content = content;
	en->prev = NULL;
	en->next = NULL;
	return (en);
}