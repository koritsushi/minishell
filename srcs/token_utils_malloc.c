/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_malloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:11:52 by hsim              #+#    #+#             */
/*   Updated: 2025/05/15 12:15:57 by hsim             ###   ########.fr       */
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

/*
 * child function in allocate_cmd_tail
 * counts number of chars in cmd_tail for malloc use
 */
static int	count_cmd_tail_chr(char **outfile)
{
	int		i;
	int		len;
	char	*cmd_tail;

	i = 0;
	len = 0;
	
	// >out cmd >out2 baba
	// len = ft_strlen(outfile[0]);
	while (outfile[i + 1])
	{
		cmd_tail = outfile[i + 1];
		cmd_tail = skip_spaces(cmd_tail, " \t\n\v\f\r");
		/* skips to the 1st space detected */
		cmd_tail = skip_if_symbol(cmd_tail, 'c', 'c');
		if (cmd_tail)
			len += (ft_strlen(cmd_tail) + 1);
		i++;
		/*debug*/printf("otail=%s| %d+1\n", cmd_tail, len);
	}
	return (len);
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
	// /*debug*/printf("aloc_cmd_tail:\n");
	// /*debug*/debug_print(outfile);

	cmd_tail = skip_spaces(outfile[0], " \t\n\v\f\r");
	cmd_tail = skip_if_symbol(cmd_tail, c, '>');
	/* split,skip by infiles */
	infile_check = ft_split_shell(skip_redirs(cmd_tail), "<");
	len = ft_strlen(infile_check[0]);
	len += count_cmd_tail_chr(infile_check);

	// cmd <in1 cmd2 <in2
	// cmd <in1 cmd2 <in2 > out -flag
	// cmd
	// in1 cmd2
	// in2

	/*debug*/printf("____alloc_cmd_tail:infile:____\n");
	/*debug*/debug_print(infile_check);
	/*debug*/printf("tail=%s| %d\n", infile_check[0], len);
	free_chr_ptr((void **)infile_check);
	
	/* count outfile & cmd_tail */
	len += count_cmd_tail_chr(outfile);
	/*debug*/printf("alloc_cmd_tail:len:%d+1\n", len);
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
