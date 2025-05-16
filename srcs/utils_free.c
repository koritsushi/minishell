/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:58:29 by hsim              #+#    #+#             */
/*   Updated: 2025/05/16 09:21:38 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/**
 * exit program if encounter any error
 * return from major function such as
 * fork, pipe, malloc, and etc
 * 
 * free all of the structs in the program
 * and print error message according to 
 * set errno message
 * 
 * exit will have exit code 1 
 */
// void	exit_free(t_ms *data, int errno)
// {
// 	printf("Error: %s\n", strerror(errno));
// 	exit(1);
// }

void	free_3d_ptr(void ***ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL)
		return ;
	while (ptr[i] != NULL)
		free_chr_ptr(ptr[i++]);
	free(ptr);
	ptr = NULL;
}

void	free_chr_ptr(void **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

/*
 * frees multiple char** pointer
 * x indicates the number of arguments passed to free
 */
void	free_multiple_ptr(char **p1, char **p2, char **p3)
{
	if (p1 != NULL)
		free_chr_ptr((void **)p1);
	if (p2 != NULL)
		free_chr_ptr((void **)p2);
	if (p3 != NULL)
		free_chr_ptr((void **)p3);
}

/*
 * frees multiple char* pointer
 * x indicates the number of arguments passed to free
 */
void	free_multiple_ptr_single(char *p1, char *p2, char *p3)
{
	if (p1 != NULL)
		free(p1);
	if (p2 != NULL)
		free(p2);
	if (p3 != NULL)
		free(p3);
}

void	free_all(t_token *lst)
{
	if (!lst)
		return ;
	free_chr_ptr((void **)lst->data);
	free(lst->datatype);
}

void	free_env(t_env *env)
{
	if (env && env->content)
		ft_lstclear_sh(&env, free);
}

void	free_exec(t_exec *exec)
{
	if (exec->cmd_args)
		free_3d_ptr((void ***)exec->cmd_args);
	if (exec->cmd)
		free_chr_ptr((void **)exec->cmd);
	if (exec->path)
		free_chr_ptr((void **)exec->path);
}

void	ms_free_all(t_ms *data, int exit_code)
{
	free_env(data->env_var);
	free_exec(&data->exec);
	if (data->lst.data)
		free_chr_ptr((void **)data->lst.data);
	if (data->lst.datatype)
		free(data->lst.datatype);
	exit(exit_code);
}
