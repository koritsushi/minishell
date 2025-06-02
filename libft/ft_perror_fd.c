/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:51:12 by hsim              #+#    #+#             */
/*   Updated: 2025/04/29 09:52:16 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * prints message in destination pointed by fd
 * value = its return value
 * have to include \n everytime
 */
int	ft_perror_fd(char *s, int fd, int value)
{
	if (!s)
		return (0);
	write(fd, s, ft_strlen(s));
	return (value);
}
