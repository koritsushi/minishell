/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:33:47 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/31 18:53:44 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(t_env *env)
{
	if (env && env->content)
		ft_lstclear_sh(&env, free);
}

void	free_exec(t_exec *exec)
{
	if (exec->cmd_args != NULL)
		free_3d_ptr((void ***)exec->cmd_args);
	if (exec->envp != NULL)
		free_chr_ptr((void **)exec->envp);
	if (exec->path != NULL)
		free_chr_ptr((void **)exec->path);
}

void	errstr_init(char *str[])
{
	str[0] = "-minishell: command allocation fail";
	str[1] = "-minishell: command allocation 2 fail";
	str[2] = "-minishell: environment allocation fail!";
	str[3] = "-minishell: environment path allocation fail!";
	str[4] = "-minishell: open() fail!";
	str[5] = "-minishell: heredoc fail!";
	str[6] = "-minishell: pipe() fail!";
	str[7] = "-minishell: fork() fail!";
	str[8] = NULL;
}

void	ms_free_all(t_ms *data, int errc, int exit_code)
{
	char	*errstr[9];

	errstr_init(errstr);
	if (errc >= 0 && errc < 8)
		perror(errstr[errc]);
	free_env(data->env_var);
	free_exec(&data->exec);
	if (data->lst.data)
		free_chr_ptr((void **)data->lst.data);
	if (data->lst.datatype)
		free(data->lst.datatype);
	rl_clear_history();
	exit(exit_code);
}
