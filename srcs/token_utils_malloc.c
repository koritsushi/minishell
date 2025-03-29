/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_malloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:11:52 by hsim              #+#    #+#             */
/*   Updated: 2025/03/29 09:18:03 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/* 
 * allocate spaces to store data for t_token list
 * uses malloc
 */
int	init_token_list(t_token *lst, int size)
{
	lst->datatype = (unsigned char *)malloc(sizeof(unsigned char) * size);
	lst->data = (char **)malloc(sizeof(char *) * size);
	while (--size >= 0)
	{
		lst->data[size] = NULL;
		lst->datatype[size] = END;
	}
	if (!lst->data || !lst->datatype)
	{
		perror("🚨 Memory allocation failed in init_token_list!");
		return (0);
	}
	return (1);
}

/*
 * mallocs a char * by size defined in len, fills all with \0
 * returns error message if malloc fails
 */
int	malloc_chr_ptr(char **dest, int len)
{
	int	x;

	x = 0;
	*dest = (char *)malloc(sizeof(char) * len);
	if (!(*dest))
	{
		perror("allocate_str: Memory allocation failed!\n");
		return (0);
	}
	while (x < len)
		(*dest)[x++] = '\0';
	return (1);
}

// 13 lines!
/*
 * child function in extract_cmd_tail
 * calculates length of cmd_tail & allocates enough size to copy to data 
 * **dest/lst_data = destination to copy str to, which = lst.data
 * str = the entire line of cmd/pipeline before splitted by outfile '>'
 * uses malloc
 */
int	allocate_cmd_tail(char **dest, char **outfile, char c)
{
	int		len;
	char	*cmd_tail;
	char	**infile_check;

	/* skip_cmd_head */
	cmd_tail = skip_spaces(outfile[0], " \t\n\v\f\r");
	cmd_tail = skip_if_symbol(cmd_tail, c, '>');
	/* split,skip by infiles */
	infile_check = ft_split_shell(cmd_tail, "<");
	len = ft_strlen(infile_check[0]);
	// /*debug*/printf("tail=%s| %d\n", infile_check[0], len);
	free_chr_ptr((void **)infile_check);

	/* count outfile & cmd_tail */
	len += count_cmd_tail_chr(outfile);
	if (!malloc_chr_ptr(dest, len + 1))
		return (0);
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
	if (!malloc_chr_ptr(dest, (ft_strlen(str) + 1)))
		return (0);
	return (1);
}
