/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:28:03 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/03 16:28:03 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	**ft_get_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (path == NULL)
		return (NULL);
	path = ft_format_path(path, "/");
	return (path);
}

char	**ft_format_path(char **path, char *format)
{
	int		i;
	char	**format_path;

	i = 0;
	while (path[i] != NULL)
		i++;
	format_path = malloc(sizeof(char *) * (i + 1));
	if (format_path == NULL)
		return (NULL);
	i = 0;
	while (path[i] != NULL)
	{
		format_path[i] = ft_strjoin(path[i], format);
		i++;
	}
	free_chr_ptr((void **) path);
	format_path[i] = NULL;
	return (format_path);
}

char	***ft_split_cmd(t_exec *exec, char **argv)
{
	char	***cmd;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	cmd = malloc(sizeof(char **) * (exec->cmd_count + 1));
	if (cmd == NULL)
		return (NULL);
	while (argv[i] != NULL && j < exec->cmd_count)
	{
		cmd[j] = ft_split_shell(argv[i++], " \t\n\v\f\r");
		k = 0;
		while (cmd[j][k] != NULL)
			quote_removal(&cmd[j][k++]);
		j++;
	}
	cmd[j] = NULL;
	return (cmd);
}

char	*ft_relative_path(char **cmd_args, char **path)
{
	int				i;
	char			*cmd_path;

	i = -1;
	if (path == NULL)
	{
		errno = ENOENT;
		return (NULL);
	}
	while (path[++i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], cmd_args[0]);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	return (cmd_path);
}
