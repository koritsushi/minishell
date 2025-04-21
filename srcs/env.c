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

void	minishell_init(t_ms *minishell, char** env)
{
	env_init(minishell->env_var, env);
}

/*	env
	used doubly linked-list to store env
	copy env from bash shell then stored a copy in minishell
*/
void	env_init(t_env env_var, char **env)
{
	char	*str;
	if (env == NULL)
		return ;
	lst->env = env;
}

void	exec_init(t_exec exec)
{

}

/*
	if update env only minishell own copy of env
*/
void	env_update(t_list **lst, t_list *lc_env)
{
	t_list new_lst;

	new_lst = ft_lstnew((void) lc_env)
	if (new_lst == NULL)
		return ;
	lst->next = ft_lstadd_back(lst, new_lst);

}

/*
	print out env from minishell 
*/
void	env_print(t_list **lst)
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
