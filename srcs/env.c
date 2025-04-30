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

void	free_strarr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

int	array_len(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str[i] != NULL)
		i++;
	return (i);
}

void	split_env(char **env, char **var)
{
	int		i;
	char	**temp;

	i = 0;
	while (env[i] != NULL)
	{
		temp = ft_split(env[i], '=');
		var[i] = ft_strdup(temp[0]);
		free_strarr(temp);
		i++;
	}
	var[i] = NULL;
}

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
	len = array_len(env);
	var = malloc(sizeof(char **) * (len + 1));
	split_env(env, var);
	while (env[i] != NULL)
	{
		if (*env_var == NULL)
		{
			*env_var = ft_lstnew_shenv(var[i], env[i], 1);
			i++;
		}
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
	exec->infile_fd = 0;
	exec->outfile_fd = 0;
	exec->here_doc = 0;
	exec->cmd_count = 0;
	exec->index = 0;
}

/*	export 
	add variable to env
*/
void	export(t_env **env_var, t_env *lenv)
{
	t_env	*iter;
	t_env	*check;
	t_env	*new;

	if (env_var == NULL || lenv == NULL)
		return ;
	iter = *env_var;
	check = lenv;
	while (iter != NULL)
	{
		if (ft_strncmp(iter->env, check->env, ft_strlen(iter->env)) == 0)
		{
			free(iter->content);
			iter->content = strdup(check->content);
			break ;
		}
		iter = iter->next;
	}
	if (iter->content == NULL)
	{
		new = ft_lstnew_env(check->env, check->content, check->exported);
		ft_lstadd_back_env(env_var, new);
	}
}

/*	unset
	remove a specific variable to display on env and export
*/
// void	unset(t_env **env_var, t_env *lenv)
// {
// 	t_env	*iter;
// 	t_env	*tmp = NULL;
// 	t_env	*prev;
// 	t_env	*check;

// 	if (env_var == NULL || lenv == NULL)
// 		return ;
// 	iter = *env_var;
// 	check = lenv;
// 	if (ft_strncmp(iter->env, check->env, ft_strlen(iter->env)) == 0)
// 	{
// 		*env_var = iter->next;
// 		ft_lstdelone_env(iter, free);
// 		return ;
// 	}
// 	iter = iter->next;
// 	while (iter != NULL)
// 	{
// 		if (ft_strncmp(iter->env, check->env, ft_strlen(iter->env)) == 0)
// 		{
// 			if (iter->next != NULL)
// 			{
// 				tmp = iter->next;
// 				prev->next = tmp;
// 			}
// 			else
// 				prev->next = NULL;
// 			ft_lstdelone_env(iter, free);
// 			iter = tmp;
// 			break ;
// 		}
// 		prev = iter;
// 		iter = iter->next;
// 	}
// }

/*
 * split input str by spaces ' '
 * iterates entire **lst & free if lst.env (env_name) == str
 * removes a specific variable that's shown on env and export
 * uses malloc
*/
void	unset(t_env **lst, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split_shell(str, " \t\n\v\f\r");

	/*debug*/printf("unset_debug_print:\n");
	debug_print(tmp);

	while (tmp[++i])
		ft_lst_remove_if(lst, tmp[i], ft_strncmp);
	free_chr_ptr((void **)tmp);
}

void	msh_init(t_ms *data, char **env)
{
	env_init(&data->env_var, env);
	exec_init(&data->exec);
}
