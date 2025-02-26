/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:11:52 by hsim              #+#    #+#             */
/*   Updated: 2025/02/26 22:32:05 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/*
 * copy src to dest with length defined in len
 * start = the index of dest to start copy to
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
 * allocate spaces to store data for t_token list
 * uses malloc
 */
int	init_token_list(t_token *lst, int size)
{
	lst->datatype = (unsigned char *)malloc(sizeof(unsigned char) * size);
	lst->data = (char **)malloc(sizeof(char *) * size);
	while (--size >= 0)
		lst->data[size] = NULL;
	if (!lst->data || !lst->datatype)
	{
		perror("🚨 Memory allocation failed in init_token_list!");
		return (0);
	}
	return (1);
}

/*
 * scans entire string and see if it has non-operators within the string
 * if contain non-operators, return (0)
 */
// int	is_all_op(char *op, char *str)
// {
// 	while (str[0])
// 	{
// 		if (!is_target(op, str[0]))
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

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
 * child function in extract_cmd_tail
 * calculates length of cmd_tail & allocates enough size to copy to data 
 * **dest/lst_data = destination to copy str to, which = lst.data
 * str = the entire line of cmd/pipeline before splitted by outfile '>'
 * uses malloc
 */
int	allocate_cmd_tail(char **dest, char **outfile, char c)
{
	int		i;
	int		len;
	char	*cmd_tail;

	i = 0;
	cmd_tail = outfile[0];
	// while (cmd_tail[0] && is_target(" \t\n\v\f\r", cmd_tail[0]))
		// cmd_tail++;
	cmd_tail = skip_spaces(outfile[0], " \t\n\v\f\r");
	cmd_tail = skip_if_symbol(cmd_tail, c, '>');
	len = ft_strlen(cmd_tail);
	/*debug*/printf("tail=%s| %d\n", cmd_tail, len);
	while (outfile[i + 1])
	{
		cmd_tail = outfile[i + 1];
		/* skips spaces */
		while (is_target(" \t\n\v\f\r", cmd_tail[0]))
			cmd_tail++;
		/* skips to the 1st space detected */
		cmd_tail = ft_strchr(cmd_tail, ' ');
		if (cmd_tail)
			len += ft_strlen(cmd_tail);
		i++;
		/*debug*/printf("otail=%s| %d+1\n", cmd_tail, len);
	}
	*dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!(*dest))
	{
		perror("allocate_str: Memory allocation failed!\n");
		return (0);
	}
	return (1);
}

/*
 * wrapper function to calculate length of str,
 * and allocates enough size to copy to data 
 * **dest = destination to copy str to, which = lst.data
 * uses malloc
 */
int	allocate_str(char **dest, char *str)
{
	if (!dest)
	{
		perror("Error! data pointer not found!\n");
		return (0);
	}
	*dest = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(*dest))
	{
		perror("allocate_str: Memory allocation failed!\n");
		return (0);
	}
	return (1);
}


/* allocate_str old version */
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
