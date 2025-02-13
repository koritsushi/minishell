/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:11:52 by hsim              #+#    #+#             */
/*   Updated: 2025/02/13 14:55:03 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/*
 * copy src to dest with length defined in len
 * start = the index to start copy
 */
void	copy_cmd(char **dest, char *src, int *start, int len)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!dest || !src)
		return ;
	if (*start > 0)
		(*dest)[(*start)++] = ' ';
	while (is_target("<>|", src[x]))
		x++;
	while (i++ < len)
		(*dest)[(*start)++] = src[x++];
	(*dest)[*start] = '\0';
	// printf("cpy=%s\n", *dest);
}

/*
 * scans entire string and see if it has non-operators within the string
 * if contain non-operators, return (0)
 */
int	is_all_op(char *op, char *str)
{
	while (str[0])
	{
		if (!is_target(op, str[0]))
			return (0);
		str++;
	}
	return (1);
}

// int	if_target_exist(char *set, char *str)
// {
// 	while (str[0])
// 	{
// 		if (is_target(set, str[0]))
// 			return (1);
// 		str++;
// 	}
// 	return (0);
// }

/* runs through char**res pointer and checks if there are pipes ahead */
// int	has_pipes(char *set, char **res)
// {
// 	int	i;
// 	// int	x;

// 	i = 0;
// 	while (res[i])
// 	{
// 		char **scan = ft_split_shell(res[i], "|");
// 		while (scan[i])
// 		{
// 			if (scan[i])
// 		}
// 		// x = 0;
// 		// if (is_target(set, res[i][0]))
// 		// 	return (1);
// 		i++;
// 	}
// 	return (0);
// }

/*
 * wrapper function for malloc enough size to copy data over 
 * int i = index to start scanning res
 */
int	allocate_str(char **res, char **data, int i)
{
	int	count;
	int	x;

	x = 0;
	count = 0;
	if (!data)
	{
		perror("Error! data pointer not found!\n");
		return (0);
	}
	while (res[i] && !is_target("<>|", res[i][0]))
	{
		count++;
		count += ft_strlen(res[i++]);
	}
	if (res[i] && (is_target("<>|", res[i][0])) && !is_all_op("<>|", res[i]))
	{
		while (res[i][x] && is_target("<>|", res[i][x]))
			x++;
		count++;
		count += ft_strlen(&res[i++][x]);
	}
	printf("alloc_count=%d\n", count);
	*data = (char *)malloc(sizeof(char) * count);
	if (!(*data))
	{
		perror("Memory allocation failed!\n");
		return (0);
	}
	return (1);
}


// int	allocate_str(char **res, char **data, int i)
// {
// 	int	count;
// 	int	x;

// 	x = 0;
// 	count = 0;
// 	if (!data)
// 	{
// 		perror("Error! data pointer not found!\n");
// 		return (0);
// 	}
// 	while (res[i] && !is_target("<>|", res[i][0]))
// 	{
// 		count++;
// 		count += ft_strlen(res[i++]);
// 	}
// 	if (res[i] && (is_target("<>|", res[i][0])) && !is_all_op("<>|", res[i]))
// 	{
// 		while (res[i][x] && is_target("<>|", res[i][x]))
// 			x++;
// 		count++;
// 		count += ft_strlen(&res[i++][x]);
// 	}
// 	printf("alloc_count=%d\n", count);
// 	*data = (char *)malloc(sizeof(char) * count);
// 	if (!(*data))
// 	{
// 		perror("Memory allocation failed!\n");
// 		return (0);
// 	}
// 	return (1);
// }
