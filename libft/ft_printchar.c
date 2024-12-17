/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:22:13 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/06 16:26:21 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_helper(va_list args)
{
	char	chr;

	chr = va_arg(args, int);
	return (ft_printchar(chr));
}

int	ft_printchar(const char chr)
{
	ft_putchar_fd(chr, 1);
	return (1);
}
