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
	t_env	*tmp;

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

/*
 * child function in ft_cd
 * checks if target_dir is relative path (eg .. or ../)
 * expand it to proper path text
 * uses malloc
 */
char	*expand_relative_path(char *str, char *curr_dir)
{
	char	*new;
	int		len;
	int		len2;

	new = str;
	len2 = 0;
	if (ft_strcmp(".", new) == 0)
		return (curr_dir);
	else if (ft_strncmp("../", new, 3) == 0 || ft_strncmp("..", new, 2) == 0)
	{
		len = ft_strrchr(curr_dir, '/') - curr_dir;
		if (ft_strchr(str, '/') && *(ft_strchr(str, '/') + 1) != '\0')
		{
			str = ft_strchr(str, '/');
			if (str[1] == '\0')
				str += 1;
			len2 = ft_strlen(str);
		}
		malloc_chr_ptr(&new, len + len2 + 1);
		ft_strlcpy(new, curr_dir, len + 1);
		if (len2 > 0)
			ft_strlcpy(&new[len], str, len2 + 1);
	}
	return (new);
}
