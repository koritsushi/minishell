/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_execute.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:30:54 by hsim              #+#    #+#             */
/*   Updated: 2025/04/30 14:17:28 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_built_in(t_ms data, int argc, char *argv)
{
	(void)	argc;
	char	**tmp;

	tmp = ft_split_shell(argv, " \t\n\v\f\r");
	// /*debug*/printf("execute_built_in:ent:%s.\n", argv[0]);
	if (strcmp(tmp[0], "echo") == 0)
	{
		ft_echo(tmp);
	}
	else if (strcmp(argv, "pwd") == 0)
	{
		ft_pwd();
	}	
	else if (strcmp(argv, "env") == 0)
	{
		env_print(&data.env_var);
	}
	else if (strcmp(argv, "export") == 0)
	{
		export_print(&data.env_var);
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
void	execute_functions(t_ms data, t_token lst)
{
	int		i;
	char	**cmd_line;

	if (!lst.data || !lst.data[0] || !lst.data[0][0])
		return ;
	cmd_line = lst.data;
	i = -1;
	if (strncmp(cmd_line[0], "cd", 2) == 0 && !has_pipes(lst))
		ft_cd(&data.env_var, ft_strchr(cmd_line[++i], ' '));
	else if (strncmp(cmd_line[0], "unset", 5) == 0 && !has_pipes(lst))
	{
		unset(&data.env_var, cmd_line[++i]);
		/*debug*/printf("\033[93m===========================\033[0m\n");
		/*debug*/env_print(&data.env_var);
	}
	while (cmd_line[++i])
	{
		/* if there's pipe || if no pipe
		 * fork & dup2 */
		if (lst.datatype[i] == WORD)
			execute_built_in(data, count_str(cmd_line[i], " \t\n\v\f\r"), cmd_line[i]);
	}
}
