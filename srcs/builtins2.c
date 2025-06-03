/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:30:46 by hsim              #+#    #+#             */
/*   Updated: 2025/06/03 14:14:23 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

/*
 * child helper function to check if all components in string
 * is digits
 */
static int	is_all_num(char *str)
{
	while (str && str[0])
	{
		if (str[0] == '-')
			str++;
		else if (!ft_isdigit(str[0]))
			return (0);
		str++;
	}
	return (1);
}

/*
 * child function for ft_exit
 * prints error message & assign exit code accordingly
 */
static int	assign_exit_code(char **argv)
{
	int	i;
	int	num;

	i = 0;
	while (argv[++i])
	{
		if (is_all_num(argv[i]))
		{
			if (argv[i + 1])
				return (ft_perror_fd("exit: too many arguments\n", 2, 1));
			num = ft_atoi(argv[i]);
			if (num > 255)
				return (num % 256);
			return (num);
		}
		return (ft_perror_fd("exit: numeric argument required\n", 2, 2));
	}
	return (0);
}

void	ft_exit(t_ms *data, char **argv)
{
	int	exit_code;

	ft_putstr_fd("\033[36mminishell exited!\033[0m\n", 1);
	exit_code = assign_exit_code(argv);
	ms_free_all(data, -1, exit_code);
}
