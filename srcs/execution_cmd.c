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
	while (envp != NULL)
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
	format_path[i] = NULL;
	return (format_path);
}

char	***ft_split_cmd(t_exec *exec, char **argv)
{
	char	***cmd;
	int		i;
	int		j;
	int		len;

	j = 0;
	len = 0;
	i = 2 + len;
	cmd = malloc(sizeof(char **) * (exec->cmd_count + 1));
	if (cmd == NULL)
		return (NULL);
	while (argv[i] != NULL && j < exec->cmd_count)
	{
		cmd[j] = ft_split(argv[i], ' ');
		i++;
		j++;
	}
	cmd[j] = NULL;
	return (cmd);
}

char	*ft_cmdpath(char **cmd_args, char **path)
{
	int		i;
	int		end;
	char	*cmd_path;

	i = -1;
	end = ft_array_len(path);
	while (path[++i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], cmd_args[0]);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
	}
	if (i == end - 1)
		return(NULL);
	return (cmd_path);
}

// void	ft_cmdpath(t_exec *exec, char **path)
// {
// 	int		i;
// 	int		j;
// 	int		end;

// 	i = -1;
// 	end = ft_str_arr(path);
// 	exec->cmd_paths = malloc(sizeof(char *) * (exec->cmd_count + 1));
// 	exec->cmd_paths[exec->cmd_count] = NULL;
// 	while (exec->cmd_args[++i] != NULL)
// 	{
// 		j = -1;
// 		while (path[++j] != NULL)
// 		{
// 			exec->cmd_paths[i] = ft_strjoin(path[j], exec->cmd_args[i][0]);
// 			if (access(exec->cmd_paths[i], F_OK) == 0)
// 				break ;
// 			if (j == end - 1)
// 			{
// 				exec->index = i;
// 				ft_cmdpath_error(exec, exec->cmd_args[i][0], path);
// 			}
// 			free(exec->cmd_paths[i]);
// 		}
// 	}
// }

// void	ft_cmdpath_error(t_ms *data, char *cmd, char **path)
// {
// 	int	i;

// 	i = 0;
// 	printf("./pipex: %s: command not found!\n", cmd);
// 	if (data->exec.cmd_args != NULL)
// 	{
// 		while (data->exec.cmd_args[i] != NULL)
// 		{
// 			ft_free(data->exec.cmd_args[i]);
// 			i++;
// 		}
// 		free(data->exec.cmd_args);
// 	}
// 	//ft_cmdpath_free(data->exec.cmd_paths, data->exec.index);
// 	//ft_free(path);
// 	exit(1);
// }