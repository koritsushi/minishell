/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:47:13 by mliyuan           #+#    #+#             */
/*   Updated: 2025/02/18 15:47:13 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

/*	env
	used singly linked-list to store env
	copy env from bash shell then stored a copy in minishell
	local variable
	environment variable wont show the variable if its empty or not exported
	uses malloc
*/
void	env_init(t_env **env_var, char **env)
{
	int		i;
	int		len;
	char	**var;
	t_env	*tmp;

	i = 0;
	len = ft_array_len(env);
	var = malloc(sizeof(char **) * (len + 1));
	tmp = *env_var;
	split_env(env, var);
	while (env[i] != NULL)
	{
		if (tmp == NULL)
		{
			tmp = ft_lstnew_shenv(var[i], env[i], 1);
			i++;
		}
		else
			tmp = ft_lstnew_shenv(var[i], env[i], 2);
		if (tmp == NULL)
			return ;
		ft_lstadd_back_env(env_var, tmp);
		i++;
	}
	free_chr_ptr((void **)var);
}

void	exec_init(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		exec->infile_fd[i] = 0;
		exec->outfile_fd[i] = 1;
		i++;
	}
	exec->path = NULL;
	exec->envp = NULL;
	exec->cmd_args = NULL;
	exec->cmd_count = 0;
	exec->pipe_count = 0;
	exec->index = 0;
}

/*
 * split input str by spaces ' '
 * iterates entire **lst & free if lst.env (env_name) == str
 * removes a specific variable that's shown on env and export
 * uses malloc
*/
int	unset(t_env **lst, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split_shell(str, " \t\n\v\f\r");
	if (tmp == NULL)
		return (-1);
	while (tmp[i] != NULL)
		ft_lst_remove_if(lst, tmp[i++], ft_strncmp);
	free_chr_ptr((void **)tmp);
	return (0);
}
