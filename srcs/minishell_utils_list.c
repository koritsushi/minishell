/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:39:22 by hsim              #+#    #+#             */
/*   Updated: 2025/04/01 08:19:50 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* modified version of linked list functions in libft 
 * ************************************************** */

#include "includes/minishell.h"

t_env	*ft_lstlast_sh(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_sh(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (lst == NULL)
		return ;
	if (lst && *lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_lstlast_sh(*lst);
		tmp->next = new;
	}
}

void	ft_lstdelone_sh(t_env *lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	if (lst && del != NULL)
	{
		(*del)(lst->content);
		free(lst);
	}
}

void	ft_lstclear_sh(t_env **lst, void (*del)(void*))
{
	t_env	*next;
	t_env	*tmp;

	if (lst == NULL)
		return ;
	if (lst && del != NULL)
	{
		tmp = *lst;
		while (tmp)
		{
			next = tmp->next;
			ft_lstdelone_sh(tmp, del);
			tmp = next;
		}
		*lst = NULL;
	}
}

t_env	*ft_lstnew_sh(void *content)
{
	t_env	*p;

	p = malloc(sizeof(t_env));
	if (p == NULL)
		return (NULL);
	p->content = content;
	p->next = NULL;
	return (p);
}
