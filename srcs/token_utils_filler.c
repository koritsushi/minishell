/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_filler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:00:07 by hsim              #+#    #+#             */
/*   Updated: 2025/05/29 14:36:07 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* helper functions for adding filler empty string to ease execution
 * if no WORD datatype detected in pipes
 * ************************************************************************** */

#include "includes/token.h"

/*
 * child function in check_copy_data
 * copies respective data
 */
static void	copy_data(t_token *dest, int *k, char *lst_data, \
unsigned char lst_datatype)
{
	dest->data[*k] = ft_strdup(lst_data);
	dest->datatype[(*k)++] = lst_datatype;
}

//24 lines!
/*
 * child function in add_filler_cmd
 * add empty string or copy respective data
 */
static void	check_copy_data(t_token *lst, t_token *dest, int flag)
{
	int	x;
	int	k;

	x = -1;
	k = 0;
	while (lst->data[++x])
	{
		// flag_cmd refresh by pipes
		// <infile | cmd | >outfile >out2 | cmd
		// <infile “” | cmd | >outfile >out2 | cmd
		if (lst->datatype[x] == WORD)
			flag = 1;
		if (!flag && (lst->datatype[x] == PIPE || \
(lst->datatype[x] == OUTFILE || lst->datatype[x] == OUTFILE_A)))
		{
			if ((lst->datatype[x] == OUTFILE || lst->datatype[x] == OUTFILE_A))
				flag = 1;
			copy_data(dest, &k, "", WORD);
			copy_data(dest, &k, lst->data[x], lst->datatype[x]);
		}
		else
			copy_data(dest, &k, lst->data[x], lst->datatype[x]);
		if (!flag && lst->data[x + 1] == NULL)
			copy_data(dest, &k, "", WORD);
		if (flag && lst->datatype[x] == PIPE) //reset
			flag = 0;
	}
}

/*
 * child function in add_filler_cmd
 * counts +=1 if there is no cmd in a pipe
 */
static int	count_realloc(t_token lst)
{
	int	x;
	int	flag;
	int	count;

	x = -1;
	flag = 0;
	count = 0;
	while (lst.data[++x])
	{
		if (lst.datatype[x] == WORD)
			flag = 1;
		else if (!flag && (lst.datatype[x] == OUTFILE || \
lst.datatype[x] == OUTFILE_A))
		{
			flag = 1;
			count++;
		}
		else if (!flag && (lst.datatype[x] == PIPE || lst.data[x + 1] == NULL))
			count++;
		if (flag && lst.datatype[x] == PIPE)
			flag = 0;
		// /*debug*/printf("x:%d  count:%d  f:%d\n", x, count, flag);
	}
	return (count);
}

/*
 * child function in get_cmd_line
 * checks if a pipe has no cmd,
 * if true, adds a empty string "" for execution purposes
 */
void	add_filler_cmd(t_token *lst)
{
	int		count;
	t_token	dest;

	count = count_realloc(*lst);
	// /*debug*/printf("add_filler_cmd:%d\n", count);
	if (!count)
		return ;
	count += count_str_array(lst->data);
	// /*debug*/printf("add_filler:malloc: %d+1\n", count);

	if (!init_token_list(&dest, count + 1))
		return ;
	check_copy_data(lst, &dest, 0);
	free_parsing(lst);
	lst->data = dest.data;
	lst->datatype = dest.datatype;
}
