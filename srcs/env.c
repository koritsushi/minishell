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
	while (arr != NULL)
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
	int	i;
	char **temp;

	i = 0;
	while (env[i] != NULL)
	{
		temp = ft_split(env[i], '=');
		var[i] = temp[0];
		//debug printf("name:%s\n", var[i]);
		i++;
	}
	var[i] = NULL;
}

/*	env
	used singly linked-list to store env
	copy env from bash shell then stored a copy in minishell
	local variable
	environment variable wont show the variable if its empty or not exported
*/
void	env_init(t_env *env_var, char **env)
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
		if (env_var == NULL)
		{
			env_var = ft_lstnew_sh(var[i], env[i], 1);
			i++;
		}
		tmp = ft_lstnew_sh(var[i], env[i], 1);
		if (tmp == NULL)
			return ;
		ft_lstadd_back_sh(&env_var, tmp);
		i++;
	}
}

void	exec_init(t_exec *exec)
{
	exec->infile_fd = 0;
	exec->outfile_fd = 0;
	exec->here_doc = 0;
	exec->cmd_count = 0;
	exec->index = 0;
}

void	msh_init(t_ms *data, char** env)
{
	env_init(data->env_var, env);
	//exec_init(data->exec);
}

/*
//if update env only minishell own copy of env
void	env_update(t_env **lst, t_env *nv)
{
	t_list new_lst;

	new_lst = ft_lstnew((void) lc_env)
	if (new_lst == NULL)
		return ;
	lst->next = ft_lstadd_back(lst, new_lst);

}


//print out env from minishell 
void	env_print(t_env **lst)
{
	int	i;

	while (lst->next != NULL)
	{
		i = 0;
		while (lst->env[i] != NULL)
			printf("%s\n", env[i++]);
		lst = lst->next;
	}
}
*/


/*	export 
	add variable to env

*/
void	export()
{

}

/*	unset
	remove a specific variale to display on env and export
*/
void	unset()
{
	
}
