/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_execute_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:37:02 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/30 17:16:40 by mliyuan          ###   ########.fr       */
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
	if (ft_strncmp(argv[0], "pwd", 3) == 0)
		status = ft_pwd();
	else if (ft_strncmp(argv[0], "env", 3) == 0)
		status = env_print(&data->env_var);
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
	else if (ft_strncmp(argv[0], "cd", 2) == 0)
	{
		if (ft_array_len(argv) >= 3)
		{
			printf("%s: too many arguments\n", argv[0]);
			return (1);
		}
		if (argv[1] != NULL)
			status = ft_cd(&data->env_var, argv[1]);
	}
	return (status);
}
