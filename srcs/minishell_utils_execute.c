/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_execute.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:30:54 by hsim              #+#    #+#             */
/*   Updated: 2025/04/30 22:09:54 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_built_in(t_ms *data, char *argv)
{
	char			**tmp;
	unsigned char	*exit_code;

	tmp = ft_split_shell(argv, " \t\n\v\f\r");
	exit_code = &data->exec.exit_code;
	if (strcmp(tmp[0], "echo") == 0)
	{
		*exit_code = ft_echo(tmp);
	}
	else if (strncmp(argv, "pwd", 3) == 0)
	{
		*exit_code = ft_pwd();
	}
	else if (strcmp(argv, "env") == 0)
	{
		*exit_code = env_print(&data->env_var);
		// env_print(&data->env_var);
	}
	else if (strcmp(argv, "export") == 0)
	{
		*exit_code = export_print(&data->env_var);
		// export_print(&data->env_var);
	}
	free_chr_ptr((void **)tmp);
}

/*
 * child function in execute_functions
 * checks if entire cmd_line has pipes
 */
static int	has_pipes(t_token lst)
{
	int	i;

	i = -1;
	while (lst.data[++i])
	{
		if (lst.datatype[i] == PIPE)
			return (1);
	}
	return (0);
}

/*
 * parent function to handle cmd_line input
 * and execute if it's built-in or execve()
 */
void	execute_functions(t_ms *data, t_token lst)
{
	int				i;
	char			**cmd_line;
	unsigned char	*exit_code;

	if (!lst.data || !lst.data[0] || !lst.data[0][0])
		return ;
	cmd_line = lst.data;
	exit_code = &data->exec.exit_code;
	i = -1;
	if (strncmp(cmd_line[0], "cd", 2) == 0 && !has_pipes(lst))
		*exit_code = ft_cd(&data->env_var, ft_strchr(cmd_line[++i], ' '));
	else if (strncmp(cmd_line[0], "unset", 5) == 0 && !has_pipes(lst))
	{
		*exit_code = unset(&data->env_var, cmd_line[++i]);
		/*debug*/printf("\033[93m===========================\033[0m\n");
		/*debug*/env_print(&data->env_var);
	}
	while (cmd_line[++i])
	{
		/* if there's pipe || if no pipe
		 * fork & dup2 */
		// int x = 0;
		// expand_exit_status(&cmd_line[i], *exit_code, &x);
		if (lst.datatype[i] == WORD)
			execute_built_in(data, cmd_line[i]);
	}
}
