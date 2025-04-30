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
	// /*debug*/printf("ft_lst_remove_if:ent: %s. %s.\n", tmp->env, target);

	if (func(tmp->env, target, ft_strlen(target)) == 0)
	{
		/*debug*/printf("ft_lst_remove_if:%s. %s.", tmp->env, target);
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

// void	ft_lstdelone_env(t_env *lst, void (*del)(void*))
// {
// 	if (lst == NULL)
// 		return ;
// 	if (lst && del != NULL)
// 	{
// 		(*del)(lst->env);
// 		(*del)(lst->content);
// 		free(lst);
// 	}
// }

// void	ft_lstclear_env(t_env **lst, void (*del)(void*))
// {
// 	t_env	*next;
// 	t_env	*tmp;

// 	if (lst == NULL)
// 		return ;
// 	if (lst && del != NULL)
// 	{
// 		tmp = *lst;
// 		while (tmp)
// 		{
// 			next = tmp->next;
// 			ft_lstdelone_env(tmp, del);
// 			tmp = next;
// 		}
// 		*lst = NULL;
// 	}
// }

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

t_env	*ft_lstnew_env(char *name, char *content, int export_id)
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
	p->content = ft_strdup(content);
	p->next = NULL;
	return (p);
}
