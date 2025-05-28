/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_execute.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:30:54 by hsim              #+#    #+#             */
/*   Updated: 2025/05/28 12:40:15 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * child function in execute_built_in
 * checks if passed string is build-in functions
 */
void	builtins_init(char *str[])
{
	str[0] = "echo";
	str[1] = "cd";
	str[2] = "pwd";
	str[3] = "env";
	str[4] = "export";
	str[5] = "unset";
	str[6] = "exit";
	str[7] = NULL;
}

int	is_built_in(char *str)
{
	char	*builtins[8];
	int		i;

	i = 0;
	builtins_init(builtins);
	while (i < 7)
	{
		if (ft_strncmp(str, builtins[i], ft_strlen(builtins[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*
 * child function in execute_functions
 * specifically handles build-in functions
 */
int	execute_built_in(t_ms *data, char **argv)
{
	int				i;
	unsigned char	*exit_code;

	i = 0;
	exit_code = &data->exec.exit_code;
	if (ft_strncmp(argv[0], "echo", 4) == 0)
		*exit_code = ft_echo(argv);
	else if (ft_strncmp(argv[0], "pwd", 3) == 0)
		*exit_code = ft_pwd();
	else if (ft_strncmp(argv[0], "env", 3) == 0 && !argv[1])
		*exit_code = env_print(&data->env_var);
	else if (ft_strncmp(argv[0], "export", 6) == 0)
		*exit_code = export_print(&data->env_var);
	else if (ft_strncmp(argv[0], "cd", 2) == 0)
		*exit_code = ft_cd(&data->env_var, argv[++i]);
	else if (ft_strncmp(argv[0], "unset", 5) == 0)
		while (argv[++i] != NULL)
			*exit_code = unset(&data->env_var, argv[i]);
	return (*exit_code);
}

/*
 * parent function to handle cmd_line input
 * and execute if it's built-in or execve()
 */
void	execute_functions(t_ms *data, t_token lst)
{
	char	**cmd;

	if (ft_isempty(lst.data[0]) || lst.data[0] == NULL)
		return ;
	ft_init_pipe(data, &lst);
	infile_parsing_init(data, &lst);
	outfile_parsing_init(data, &lst);
	cmd = ft_cmd_init(data, &lst);
	if (cmd == NULL)
		ms_free_all(data, 0, 1);
	data->exec.cmd_args = ft_split_cmd(&data->exec, cmd);
	if (data->exec.cmd_args == NULL)
		return (free_chr_ptr((void **) cmd), ms_free_all(data, 1, 1));
	free_chr_ptr((void **) cmd);
	if ((has_pipes(lst) == 0 && has_infile_outfile(lst) == 0) && \
is_built_in(data->exec.cmd_args[0][0]) == 1)
		return ((void) execute_built_in(data, data->exec.cmd_args[0]));
	data->exec.envp = ft_envp(&data->env_var);
	if (data->exec.envp == NULL)
		ms_free_all(data, 2, 1);
	data->exec.path = ft_get_path(data->exec.envp);
	if (data->exec.path == NULL)
		return (free_chr_ptr((void **) cmd), ms_free_all(data, 3, 1));
	ft_process(data);
}
