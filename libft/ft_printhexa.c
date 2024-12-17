/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:02:22 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/06 16:26:20 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexa_upper_helper(va_list args)
{
	unsigned long	num;

	num = va_arg(args, unsigned int);
	return (ft_printhexa_upper(num));
}

int	ft_printhexa_upper(unsigned long num)
{
	int		i;
	int		strlen;
	char	*str;
	char	*base;

	if (num == 0)
		return (ft_printchar('0'));
	strlen = 0;
	base = "0123456789ABCDEF";
	i = 0;
	str = malloc(sizeof(char *) * 8);
	while (num != 0)
	{
		str[i] = base[num % 16];
		num = num / 16;
		i++;
	}
	while (i--)
		strlen += ft_printchar(str[i]);
	free(str);
	return (strlen);
}

int	ft_hexa_lower_helper(va_list args)
{
	unsigned long	num;

	num = va_arg(args, unsigned int);
	return (ft_printhexa_lower(num));
}

int	ft_printhexa_lower(unsigned long num)
{
	int		i;
	int		strlen;
	char	*str;
	char	*base;

	if (num == 0)
		return (ft_printchar('0'));
	strlen = 0;
	base = "0123456789abcdef";
	i = 0;
	str = malloc(sizeof(char *) * 8);
	while (num != 0)
	{
		str[i] = base[num % 16];
		num = num / 16;
		i++;
	}
	while (i--)
		strlen += ft_printchar(str[i]);
	free(str);
	return (strlen);
}
