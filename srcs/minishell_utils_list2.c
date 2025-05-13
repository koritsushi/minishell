/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_list2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 21:34:40 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/03 21:34:40 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_lstsize_sh(t_env **lst)
{
	t_env *tmp;
	int	i;

	i = 0;
	tmp = *lst;
	if (lst == NULL)
		return (i);
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}