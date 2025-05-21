/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:33:47 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/21 11:40:30 by mliyuan          ###   ########.fr       */
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
	if (exec->cmd_args)
		free_3d_ptr((void ***)exec->cmd_args);
	if (exec->cmd)
		free_chr_ptr((void **)exec->cmd);
	if (exec->path)
		free_chr_ptr((void **)exec->path);
}

void	ms_free_all(t_ms *data, int exit_code)
{
	free_env(data->env_var);
	free_exec(&data->exec);
	if (data->lst.data)
		free_chr_ptr((void **)data->lst.data);
	if (data->lst.datatype)
		free(data->lst.datatype);
	exit(exit_code);
}
