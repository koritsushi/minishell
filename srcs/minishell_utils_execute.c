/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_execute.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:30:54 by hsim              #+#    #+#             */
/*   Updated: 2025/05/30 17:36:31 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * child function in execute_built_in
 * checks if passed string is build-in functions
 */
void	builtins_init(char *str[])
{
	str[0] = "exit";
	str[1] = "pwd";
	str[2] = "env";
	str[3] = "cd";
	str[4] = "echo";
	str[5] = "export";
	str[6] = "unset";
	str[7] = NULL;
}

int	is_built_in(char *str)
{
	char	*builtins[8];
	int		i;

	i = 0;
	builtins_init(builtins);
	if (ft_isempty(str))
		return (0);
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(str, builtins[i]) == 0)
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
	char			*builtins[8];		
	unsigned char	*exit_code;

	i = 0;
	builtins_init(builtins);
	exit_code = &data->exec.exit_code;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(argv[0], builtins[i], ft_strlen(argv[0])) == 0 && i <= 2)
			return (*exit_code = singular_args_builtins(data, argv));
		else if (ft_strncmp(argv[0], builtins[i], ft_strlen(argv[0])) == 0 \
&& i > 2)
			return (*exit_code = multiple_args_builtins(data, argv));
		i++;
	}
	return (*exit_code);
}

/*
 * parent function to handle cmd_line input
 * and execute if it's built-in or execve()
 */
void	execute_functions(t_ms *data, t_token lst)
{
	char	**cmd;

	if (lst.data == NULL || lst.data[0] == NULL)
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
is_built_in(data->exec.cmd_args[0][0]))
		return ((void) execute_built_in(data, data->exec.cmd_args[0]));
	data->exec.envp = ft_envp(&data->env_var);
	if (data->exec.envp == NULL)
		ms_free_all(data, 2, 1);
	data->exec.path = ft_get_path(data->exec.envp);
	if (data->exec.path == NULL)
		return (free_chr_ptr((void **) cmd), ms_free_all(data, 3, 1));
	ft_process(data);
}
