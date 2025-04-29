/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:58:29 by hsim              #+#    #+#             */
/*   Updated: 2025/04/29 17:13:53 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

void	free_chr_ptr(void **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

/*
 * frees multiple char** pointer
 * x indicates the number of arguments passed to free
 */
void	free_multiple_ptr(char **p1, char **p2, char **p3)
{
	if (p1 != NULL)
		free_chr_ptr((void **)p1);
	if (p2 != NULL)
		free_chr_ptr((void **)p2);
	if (p3 != NULL)
		free_chr_ptr((void **)p3);
}

/*
 * frees multiple char* pointer
 * x indicates the number of arguments passed to free
 */
void	free_multiple_ptr_single(char *p1, char *p2, char *p3)
{
	if (p1 != NULL)
		free(p1);
	if (p2 != NULL)
		free(p2);
	if (p3 != NULL)
		free(p3);
}

void	free_all(t_token *lst)
{
	if (!lst)
		return ;
	free_chr_ptr((void **)lst->data);
	free(lst->datatype);
}
