/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_execute.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:30:54 by hsim              #+#    #+#             */
/*   Updated: 2025/05/13 14:52:44 by hsim             ###   ########.fr       */
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

	i = -1;
	while (lst.data[++i])
	{
		if (lst.datatype[i] == PIPE)
			return (1);
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
	str[1] = "pwd";
	str[2] = "env";
	str[3] = "export";
	str[4] = NULL;
 }

int is_built_in(char *str)
{
	char	*builtins[4];
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
	/*
	if ((strcmp(str, "echo") == 0) || \
(strncmp(str, "pwd", 3) == 0) || \
(strcmp(str, "env") == 0) || \
(strcmp(str, "export") == 0))
	return (1);
	return (0);
	*/
}

/*
 * child function in execute_functions
 * specifically handles build-in functions
 */
int	execute_built_in(t_ms *data, char **argv)
{
	//char			**tmp;
	unsigned char	*exit_code;

	exit_code = &data->exec.exit_code;
	//tmp = ft_split_shell(argv, " \t\n\v\f\r");
	if (!is_built_in(argv[0]))
	{
		//free_chr_ptr((void **)tmp);
		return (0);
	}
	if (ft_strncmp(argv[0], "echo", 4) == 0)
		*exit_code = ft_echo(argv);
	else if (ft_strncmp(argv[0], "pwd", 3) == 0)
		*exit_code = ft_pwd();
	else if (ft_strncmp(argv[0], "env", 3) == 0)
		*exit_code = env_print(&data->env_var);
	else if (ft_strncmp(argv[0], "export", 6) == 0)
		*exit_code = export_print(&data->env_var);
	//free_chr_ptr((void **)tmp);
	return (1);
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
	if (has_pipes(lst))
	{
		infile_parsing_init(data, &lst);
		outfile_parsing_init(data, &lst);
		ft_execs_init(data, &lst);
	}

	// while (cmd_line[++i]) //split into another function here
	// {
	// 	/* if there's pipe || if no pipe
	// 	 * fork & dup2 */
	// 	// /*debug*/printf("execute_functions:%d\n", data->exec.exit_code);
	// 	// /*debug*/printf("execute_functions:$?:ent:\033[93m%s\033[0m.\n", cmd_line[i]);
	// 	/*debug*/printf("execute_functions:$?:\033[92m%s\033[0m.\n", cmd_line[i]);
	// 	if (lst.datatype[i] == WORD)
	// 		execute_built_in(data, cmd_line[i]);
	// }
}
