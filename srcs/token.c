/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:56:04 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/14 19:56:04 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

int	init_token_list(t_token *lst, int size)
{
	lst->datatype = (unsigned char *)malloc(sizeof(unsigned char) * size);
	lst->data = (char **)malloc(sizeof(char *) * size);
	if (!lst->data || !lst->datatype)
	{
		perror("🚨 Memory allocation failed in init_token_list!\n");
		return (0);
	}
	return (1);
}

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
	while (i++ < len)
		(*dest)[(*start)++] = src[x++];
	(*dest)[*start] = '\0';
}

/*
 * wrapper function for malloc enough size to copy data over 
 * int i = index to start scanning res
 */
int	allocate_str(char **res, char **data, int i)
{
	int	count;

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
	*data = (char *)malloc(sizeof(char) * count);
	if (!(*data))
	{
		perror("Memory allocation failed!\n");
		return (0);
	}
	return (1);
}

void	identify_op(char *str, unsigned char *datatype)
{
	if (!str)
	{
		*datatype = END;
		return ;
	}
	if (str[0] && is_target("<", str[0]))
	{
		if (str[1] && is_target("<", str[1]) && str[2] == '\0')
			*datatype = HEREDOC;
		else if (str[1] == '\0' && is_target("<", str[0]))
			*datatype = INFILE;
		else
			*datatype = ERR;
	}
	else if (str[0] && is_target(">", str[0]))
	{
		if (str[1] && is_target(">", str[1]) && str[2] == '\0')
			*datatype = OUTFILE_A;
		else if (str[1] == '\0' && is_target(">", str[0]))
			*datatype = OUTFILE;
		else
			*datatype = ERR;
	}
	else
		*datatype = WORD;
}

/* scans input and assigns datatype according to operator sign */
void	assign_datatype(t_token *lst, char **res)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	identify_op(res[i], &lst->datatype[x++]);
	while (res[i])
	{
		while (res[i] && !is_target("<>|", res[i][0]))
			i++;
		identify_op(res[i++], &lst->datatype[x++]);
	}
}

void	recombine_cmd(char **res, t_token *lst)
{
	int i;
	int	x;
	int	start;

	i = 0;
	x = 0;
	while (res[i])
	{
		allocate_str(res, &lst->data[x], i);
		start = 0;
		while (res[i] && !is_target("<>|", res[i][0]))
		{
			copy_cmd(&lst->data[x], res[i], &start, ft_strlen(res[i]));
			i++;
		}
		printf("str%d=%s| start= %d\n", x, lst->data[x], start);
		x++;
		while (res[i] && is_target("<>|", res[i][0]))
			i++;
	}
	lst->data[x] = NULL;
}

/*
 * splits input by PIPE & REDIR, stores result in allocated t_token pointer
 * uses malloc
 */
void	get_cmd_line(char *str, t_token *lst)
{
	char	**res;
	int		i;
	int		count_op;

	if (!str)
		return ;
	res = ft_split_shell(str, " \t\n\v\f\r");
	count_op = 0;
	i = 0;
	while (res[i])
	{
		if (is_target("<>|", res[i++][0]))
			count_op++;
	}
	if (!init_token_list(lst, count_op + 2))
		return ;
	assign_datatype(lst, res);
	recombine_cmd(res, lst);

	/*-------------debug_start-------------*/
	printf("\n\n");
	i = -1;
	while (++i < count_op + 2)
		printf("%s| %d\n", lst->data[i], lst->datatype[i]);
	/*--------------debug_end--------------*/
	free_chr_ptr((void **)res);
	return ;
}
