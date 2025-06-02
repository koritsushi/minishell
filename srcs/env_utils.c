/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:16:05 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/20 21:16:05 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

/*
 * checks if lst.env (env_name) == target
 * if true, frees the entry
 * function pointer *func is ft_strcmp()
 */
void	ft_lst_remove_if(t_env **lst, char *target, int (*func)())
{
	t_env	*tmp;

	if (!lst || !*lst)
		return ;
	tmp = *lst;
	if (func(tmp->env, target, ft_strlen(target)) == 0)
	{
		(*lst) = tmp->next;
		free_multiple_ptr_single(tmp->env, tmp->content, NULL);
		free(tmp);
		ft_lst_remove_if(lst, target, func);
	}
	else
	{
		tmp = *lst;
		ft_lst_remove_if(&tmp->next, target, func);
	}
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (lst == NULL)
		return ;
	if (lst && *lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_lstlast_env(*lst);
		tmp->next = new;
	}
}

/*
 * helper function in saving variable in linked list
 * splits var=123 into var and 123, saves in linked list
 * and return the updated t_env
 * uses malloc
 */
t_env	*ft_lstnew_shenv(char *name, char *content, int export_id)
{
	t_env	*p;

	p = malloc(sizeof(t_env));
	if (p == NULL)
		return (NULL);
	p->env = ft_strdup(name);
	p->exported = export_id;
	if (!is_target(content, '='))
		p->exported = 1;
	if (!is_target(content, '='))
		p->content = ft_strdup("");
	else if (ft_strchr(content, '='))
		p->content = ft_strdup(ft_strchr(content, '=') + 1);
	p->next = NULL;
	return (p);
}
