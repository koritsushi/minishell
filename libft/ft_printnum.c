/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:25:12 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/06 16:26:18 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_num_helper(va_list args)
{
	int	num;

	num = va_arg(args, int);
	return (ft_printnum(num));
}

int	ft_printnum(int num)
{
	char	*str;
	int		strlen;

	str = ft_itoa(num);
	strlen = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (strlen);
}
