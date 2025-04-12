/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:39:22 by hsim              #+#    #+#             */
/*   Updated: 2025/04/12 13:49:51 by hsim             ###   ########.fr       */
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
		(*del)(lst->env);
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

/*
 * helper function in saving variable in linked list
 * splits var=123 into var and 123, saves in linked list
 * and return the updated t_env
 * uses malloc
 */
t_env	*ft_lstnew_sh(char *name, char *content, int export_id)
{
	t_env	*p;

	p = malloc(sizeof(t_env));
	if (p == NULL)
		return (NULL);

	// get_var_name(&name, content);
	// quote_removal(&name);
	p->env = ft_strdup(name);

	p->exported = export_id;
	if (!is_target(content, '='))
		p->exported = 1;

	if (!is_target(content, '='))
		p->content = ft_strdup("");
	else if (ft_strchr(content, '='))
		p->content = ft_strdup(ft_strchr(content, '=') + 1);
	/*debug*/printf("ft_lstnew_sh:content:%s.\n", p->content);
	p->next = NULL;
	return (p);
}
