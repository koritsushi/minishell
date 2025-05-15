/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_remove.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:20:26 by hsim              #+#    #+#             */
/*   Updated: 2025/05/15 12:21:12 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

/*
 * child function in remove_var
 * moves strings along char ** to the left & remove entire entry
 */
static void	remove_var_line(t_token *lst, int i)
{
	int	k;

	k = i;
	// str k     | str k+1 |  NULL
	// var=123   : free & NULL
	while (lst->data[k] && lst->data[k + 1])
	{
		free(lst->data[k]); //(remove entire char* entry)
		// if k+1 == pipe && k+2 pass check_var_syntax
		// free k, if k+1 == pipe, strdup k+2
		lst->data[k] = ft_strdup(lst->data[k + 1]); //(move entire char* left)
		lst->datatype[k] = lst->datatype[k + 1]; //(move entire char* left)
		k++;
	}
	free(lst->data[k]); //(remove entire char* entry)
	lst->data[k] = NULL;
	lst->datatype[k] = END;
}

/*
 * child function in remove_var
 * removes any pipes that is in front & back
 */
static void	remove_pipe_front(t_token *lst)
{
	int	i;

	i = 0;
	/*debug*/printf("pikachu.\n");
	
	// /*debug*/printf("remove_pipe:%s. %d\n", lst->data[i], lst->datatype[i]);
	while (lst->data[i] && lst->datatype[i] == PIPE)
	{
		/*debug*/printf("remove_pipe_f:%s.\n", lst->data[i]);
		remove_var_line(lst, i);
	}
	while (lst->data[i + 1])
		i++;
	while (i >= 0 && lst->datatype[i] == PIPE)
		remove_var_line(lst, i--);
}

/*
 * child function in get_variable
 * trims all cmd_line to skip or free valid var assignment (var=123)
 * so that it dont get passed to execution
 */
void	remove_var(t_token *lst)
{
	int		i;
	// int		k;

	i = -1;
	debug_print_cmd_line(lst);
	/*debug*/printf("pika.\n");

	while (lst->data[++i]) //0
	{
		//go to word
		while (lst->data[i] && lst->datatype[i] != WORD)
			i++;
		if (!lst->data[i] || !lst->data[i][0])
			break ;
		//trim cmd in check_var_syntax
		//free cmd if check_var_syntax OK
		/*debug*/printf("remove_var:%s.\n", lst->data[i]);
		if (check_var_syntax(&lst->data[i]))
			remove_var_line(lst, i);
	}
	remove_pipe_front(lst);
}