/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:58:29 by hsim              #+#    #+#             */
/*   Updated: 2025/02/12 21:01:09 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

void	free_chr_ptr(void **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	free_all(t_token *lst)
{
	if (!lst)
		return ;
	free_chr_ptr((void **)lst->data);
	// free(lst->datatype);
}
