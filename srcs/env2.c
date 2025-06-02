/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:43:41 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/21 11:44:07 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

void	free_strarr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

int	ft_array_len(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str[i] != NULL)
		i++;
	return (i);
}

void	split_env(char **env, char **var)
{
	int		i;
	char	**temp;

	i = 0;
	while (env[i] != NULL)
	{
		temp = ft_split(env[i], '=');
		var[i] = ft_strdup(temp[0]);
		free_strarr(temp);
		i++;
	}
	var[i] = NULL;
}
