/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_execute_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:37:02 by mliyuan           #+#    #+#             */
/*   Updated: 2025/06/03 08:37:54 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	singular_args_builtins(t_ms *data, char **argv)
{
	int	status;

	status = 0;
	if (ft_array_len(argv) > 1)
	{
		printf("%s: too many arguments\n", argv[0]);
		return (1);
	}
	else if (ft_strncmp(argv[0], "pwd", 3) == 0)
		status = ft_pwd();
	else if (ft_strncmp(argv[0], "env", 3) == 0)
		status = env_print(&data->env_var);
	return (status);
}

/* wrapper function for ft_cd to reduce lines */
int	execute_ft_cd(t_ms *data, char **argv)
{
	int	status;

	status = 0;
	if (ft_array_len(argv) >= 3)
		return (ft_perror_fd("cd: too many arguments\n", 2, 1));
	if (argv[1] != NULL && ft_isempty(argv[1]) == 0)
		status = ft_cd(&data->env_var, argv[1]);
	else
		return (ft_perror_fd("cd: invalid argument!\n", 2, 1));
	return (status);
}

int	multiple_args_builtins(t_ms *data, char **argv)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (ft_strncmp(argv[0], "echo", 4) == 0)
		status = ft_echo(argv);
	else if (ft_strncmp(argv[0], "export", 6) == 0)
		status = export_print(&data->env_var);
	else if (ft_strncmp(argv[0], "unset", 5) == 0)
		while (argv[i] != NULL)
			status = unset(&data->env_var, argv[++i]);
	else if (ft_strncmp(argv[0], "exit", 4) == 0)
		ft_exit(data, argv);
	else if (ft_strncmp(argv[0], "cd", 2) == 0)
		status = execute_ft_cd(data, argv);
	return (status);
}
