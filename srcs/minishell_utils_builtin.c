/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_builtin.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:30:54 by hsim              #+#    #+#             */
/*   Updated: 2025/04/29 17:17:11 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_built_in(t_ms data, int argc, char **argv)
{
	/*debug*/printf("execute_built_in:ent:%s.\n", argv[0]);
	if (strcmp(argv[0], "echo") == 0)
	{
		ft_echo(argc, &argv[0]);
	}
	else if (strcmp(argv[0], "pwd") == 0)
	{
		ft_pwd();
	}	
	else if (strcmp(argv[0], "cd") == 0)
	{
		ft_pwd();
		ft_cd(&data.env_var, argv[1]);
		ft_pwd();
	}
	else if (strcmp(argv[0], "env") == 0)
	{
		env_print(&data.env_var);
	}
	else if (strcmp(argv[0], "export") == 0)
	{
		export_print(&data.env_var);
	}
	else if (strncmp(argv[0], "unset", 5) == 0)
	{
		unset(&data.env_var, argv[0]);
		printf("\033[93m===========================\033[0m\n");
		env_print(&data.env_var);
	}
}
