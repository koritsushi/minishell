/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:03:43 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/31 17:49:48 by mliyuan          ###   ########.fr       */
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
	char			*cmd_path;
	struct stat		sb;

	cmd_path = ft_strdup(cmd);
	if (cmd_path == NULL)
		return (NULL);
	if ((stat(cmd_path, &sb) == 0 && (sb.st_mode & S_IXUSR)))
	{
		if (S_ISDIR(sb.st_mode) != 0)
			errno = EISDIR;
		else
			return (cmd_path);
	}
	else
	{
		if (access(cmd_path, F_OK) == 0)
			errno = EACCES;
	}
	free(cmd_path);
	return (NULL);
}
