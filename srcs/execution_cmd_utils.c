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
	if (envp == NULL)
		return (NULL);
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

char	*ft_absolute_path(char *cmd)
{
	char	*pwd;
	char	*cmd_path;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	pwd = getpwd();
	cmd_path = ft_strjoin(pwd, cmd);
	if (access(cmd_path, F_OK) == 0)
		return (cmd_path);
	free_multiple_ptr_single(cmd_path, pwd, NULL);
	return (NULL);
}
