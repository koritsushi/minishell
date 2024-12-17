/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:50:50 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/06 16:25:53 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_flag(int (*function[])())
{
	function[0] = ft_char_helper;
	function[1] = ft_str_helper;
	function[2] = ft_num_helper;
	function[3] = ft_num_helper;
	function[4] = ft_uint_helper;
	function[5] = ft_hexa_lower_helper;
	function[6] = ft_hexa_upper_helper;
	function[7] = ft_memory_helper;
}

static int	ft_formatspecifier(const char format, va_list args)
{
	int			(*conv_func[8])(va_list);
	char		*type;
	int			i;

	i = 0;
	type = "csdiuxXp%";
	init_flag(conv_func);
	while (type[i] != '\0')
	{
		if (type[i] == format)
			return (conv_func[i](args));
		else if (format == '%')
			return (ft_printchar('%'));
		i++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		strlen;
	va_list	args;

	if (str == NULL)
	{
		ft_printstr("(null)");
		return (6);
	}
	strlen = 0;
	va_start(args, str);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			strlen += ft_formatspecifier(*(str + 1), args);
			str++;
		}
		else
			strlen += ft_printchar(*str);
		str++;
	}
	va_end(args);
	return (strlen);
}
