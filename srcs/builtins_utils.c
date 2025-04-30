/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:14:52 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/22 12:14:52 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

/*
 * checks if name = lst.env_name
 * if found, replace lst content with char *content
 */
void	ft_lst_replace_if(t_env *lst, char *name, char *content)
{
    t_env   *tmp;

    if (!lst || !content)
        return ;
    tmp = lst;
    if (ft_strncmp(tmp->env, name, ft_strlen(name)) == 0)
    {
        free(tmp->content);
        tmp->content = ft_strdup(content);
        ft_lst_replace_if(tmp->next, name, content);
    }
    else
        ft_lst_replace_if(tmp->next, name, content);
}