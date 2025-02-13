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
		while (res[i])// && !is_target("<>|", res[i][0]))
		{
			if (is_target("<>|", res[i][0]) && res[i][1] == '\0')
				break ;
			i++;
		}
		if (res[i])
			identify_op(res[i++], &lst->datatype[x++]);
		else
			lst->datatype[x] = END;
	}
}

void	recombine_cmd(char **res, t_token *lst)
{
	int		i;
	int		x;
	int		start;

	i = 0;
	x = 0;
	while (res[i])
	{
		allocate_str(res, &lst->data[x], i);
		start = 0;
		while (res[i])// && !is_target("<>|", res[i][0]))
		{
			if (is_target("<>|", res[i][0]) && is_all_op("<>|", res[i]))
				break ;
			copy_cmd(&lst->data[x], res[i], &start, ft_strlen(res[i]));
			i++;
		}
		// // printf("str%d=%s| start= %d\n", x, lst->data[x], start);
		x++;
		while (res[i] && is_target("<>|", res[i][0]))
			i++;
	}
	lst->data[x] = NULL;
}

static int	count_str_array(char **res)
{
	int i;

	i = 0;
	while (res[i])
		i++;
	return (i - 1);
}

/*
 * counts number of string combos for malloc later
 * checks if < << is at beginning, process entire line til pipe
 * if infile at middle, all strings after < are filenames
 */
void	get_malloc_size(int *count_op, int *pipe_flag, char *str)
{
	int		i;
	char	**res;
	char	**file[2];

	i = -1;
	*count_op = 0;
	*pipe_flag = 0;
	if (!str)
		return ;
	res = ft_split_shell(str, "|");
	file[IN] = ft_split_shell(res[0], "<");
	i = count_str_array(res);
	file[OUT] = ft_split_shell(res[i], ">");

	// /* check if has pipe, pipe_flag=1 */

	// /* below only apply if pipe_flag=0 */
	// if (is_target("<", res[0][0])) // checks beginning
	// {
	// 	(*count_op)++;
	// 	i++; //0
	// 	if (res[i + 1] && res[i + 2])
	// 		(*count_op)++;
	// }
	// while (res[++i])
	// {
	// 	printf("i=%d\n", i);
	// 	if (is_target("<>|", res[i][0]))
	// 		(*count_op)++;
	// 	if (is_target("|", res[i][0]))
	// 		(*pipe_flag) = 1;
	// 	// i++;
	// }
}

/*
 * splits input by PIPE & REDIR, stores result in allocated t_token pointer
 * uses malloc
 */
void	get_cmd_line(char *str, t_token *lst)
{
	(void)	lst;
	char	**res;
	int		pipe_flag;
	int		count_op;

	if (!str || !str[0])
		return ;
	res = ft_split_shell(str, " \t\n\v\f\r");
	// res = ft_split_shell(str, "|");
	debug_print(res);

	// get_malloc_size(&count_op, &pipe_flag, str);
	// printf("op=%d f=%d\n", count_op, pipe_flag);
	// if (!init_token_list(lst, (count_op + 1 + pipe_flag)))
	// 	return ;

	// recombine_cmd(res, lst);
	// assign_datatype(lst, res);

	/*-------------debug_start-------------*/
	// printf("\n-------\n");
	// int i = -1;
	// while (++i < count_op + 2)
	// 	printf("%s| \n", lst->data[i]);//, lst->datatype[i]);
	/*--------------debug_end--------------*/
	free_chr_ptr((void **)res);
}
