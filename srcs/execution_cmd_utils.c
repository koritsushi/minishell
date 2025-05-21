/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:28:00 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/03 16:28:00 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	**ft_envp(t_env **lst)
{
	char	**envp;
	char	*env;
	t_env	*tmp;
	int		i;

	if (lst == NULL)
		return (NULL);
	i = 0;
	tmp = *lst;
	envp = malloc(sizeof(char *) * (ft_lstsize_sh(lst) + 1));
	while (tmp != NULL)
	{
		env = ft_strjoin(tmp->env, "=");
		envp[i] = ft_strjoin(env, tmp->content);
		free(env);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
