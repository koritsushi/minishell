/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuurin98 <yuurin98@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 01:06:07 by yuurin98          #+#    #+#             */
/*   Updated: 2024/12/28 01:15:09 by yuurin98         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_check_n(char	*s)
{
	if (s[0] != '-')
		return (false);
	while (s)
	{
		if (*s != 'n')
			return (false);
		s++;
	}
	return (true);
}

int	ft_echo(char **args)
{
	int		i;
	bool	n;
	
	i = 1;
	n = false;
	while (args[i] != NULL && ft_check_n(args[i]) == true)
	{
		n = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n == true)
		ft_putstr_fd("\n", 1);
	return (0);
}