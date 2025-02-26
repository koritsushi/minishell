/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:58:29 by hsim              #+#    #+#             */
/*   Updated: 2025/02/25 07:45:19 by hsim             ###   ########.fr       */
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
void	free_multiple_ptr(int x, ...)
{
	va_list	args;

	va_start(args, x);
	while (x > 0)
	{
		free_chr_ptr((void **)(va_arg(args, char **)));
		x--;
	}
	va_end(args);
}

void	free_all(t_token *lst)
{
	if (!lst)
		return ;
	free_chr_ptr((void **)lst->data);
	free(lst->datatype);
}
