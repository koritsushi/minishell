/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:03:43 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/29 14:09:40 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_isempty(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	lst_cmd_count(t_token *lst)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i++] == WORD)
			size++;
	}
	return (size);
}

int	lst_pipe_count(t_token *lst)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (lst->data[i] != NULL)
	{
		if (lst->datatype[i] == PIPE)
			size++;
		i++;
	}
	return (size);
}
