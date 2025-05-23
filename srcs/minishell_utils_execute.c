/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_execute.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:30:54 by hsim              #+#    #+#             */
/*   Updated: 2025/05/23 15:32:20 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * child function in execute_functions
 * checks if entire cmd_line has pipes
 */
int	has_pipes(t_token lst)
{
	int	i;

	i = 0;
	while (lst.data[i])
	{
		if (lst.datatype[i] == PIPE)
			return (1);
		i++;
	}
	return (0);
}

int has_infile_outfile(t_token lst)
{
	int	i;

	i = 0;
	while (lst.data[i])
	{
		if (lst.datatype[i] == INFILE || lst.datatype[i] == HEREDOC)
			return (1);
		if (lst.datatype[i] == OUTFILE || lst.datatype[i] == OUTFILE_A)
			return (1);
		i++;
	}
	return (0);
}

/*
 * child function in execute_functions
 * expand $? before executing cmd
 * replace cmd_line with the expanded content
 * updates int to the index after expansion
 * uses malloc
 */
// static void	expand_exit_mod(char **cmd_line, int exit_status)
// {
// 	int		x;
// 	char	*str;

// 	x = 0;
// 	str = *cmd_line;
// 	while (str && str[x])
// 	{
// 		/*debug*/printf("\033[43mexpand_exit_mod:\033[0ment:%s.\n", &str[x]);
// 		if (ft_strncmp(&str[x], "$?", 2) == 0)
// 			str = expand_exit_status(cmd_line, exit_status, &x);
// 		else
// 			x++;
// 		/*debug*/printf("\033[43mexpand_exit_mod:\033[0mend:%s. %s.\n", str, &str[x]);
// 	}

// }

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

int is_built_in(char *str)
{
	char	*builtins[8];
	int		i;

	i = 0;
	builtins_init(builtins);
	while (builtins[i] != NULL)
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
		while (argv[i] != NULL)
			*exit_code = unset(&data->env_var, argv[i++]);
	return (*exit_code);
}

/*
 * parent function to handle cmd_line input
 * and execute if it's built-in or execve()
 */
void	execute_functions(t_ms *data, t_token lst)
{
	char	**cmd;

	ft_init_pipe(data, &lst);
	infile_parsing_init(data, &lst);
	outfile_parsing_init(data, &lst);
	cmd = ft_cmd_init(data, &lst);
	if (cmd == NULL)
	{
		printf("-minishell: command allocation fail!: Critical Error!\n");
		ms_free_all(data, 1); //cmd allocation fail exit minishell program free everything
	}
	data->exec.cmd_args = ft_split_cmd(&data->exec, cmd);
	if (data->exec.cmd_args == NULL)
	{
		free_chr_ptr((void **) cmd);
		printf("-minishell: split 3 dimensional command array allocation fail!: Critical Error!\n");
		ms_free_all(data, 1);  //split 3d cmd fail, exit minishell program free everything
	}
	free_chr_ptr((void **) cmd);
	if (is_built_in(data->exec.cmd_args[0][0]) && \
	(has_pipes(lst) == 0 || has_infile_outfile(lst) == 0))
	{
		printf("hello\n");
		execute_built_in(data, data->exec.cmd_args[0]);
		return ;
	}
	data->exec.envp = ft_envp(&data->env_var);
	if (data->exec.envp == NULL)
	{
		printf("-minishell: environment allocation fail!: Critical Error!\n");
		ms_free_all(data, 1); //envp allocation fail exit minishell program free everything
	}
	data->exec.path = ft_get_path(data->exec.envp);
	if (data->exec.path == NULL)
	{
		free_chr_ptr((void **) cmd);
		printf("-minishell: environment path allocation fail!: Critical Error!\n");
		ms_free_all(data, 1); //get path fail, exit minishell program free everything
	}
	ft_process(data);
}
