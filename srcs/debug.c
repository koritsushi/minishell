/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:25:46 by hsim              #+#    #+#             */
/*   Updated: 2025/05/06 14:40:41 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   helper functions for debug purposes
 * ************************************************************************** */

#include "includes/minishell.h"

void	debug_print(char **res)
{
	int	i = 0;

	if (!res)
	{
		printf("NULL\n");
		return ;
	}
	while (res && res[i])
		printf("%s.\n", res[i++]);
}

void	debug_print_cd(void)
{
	char tab[100];
	printf("path:%s.\n", getcwd(tab, 100));
}

void	debug_print_cmd_line(t_token *lst)
{
	int	i;

	i = -1;
	printf("\n\033[102m_____lst_data:_____\033[0m\n");
	while (lst->data[++i])
		printf("\033[92mdata:[%s]\033[0m. datatype:[%d]\n", lst->data[i], lst->datatype[i]);
}

void	debug_print_var_lst(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	/*debug*/printf("\033[90m_____export_id definition:_____\033[0m\n");
	/*debug*/printf("\033[90m0:[0]env_list && [0]export_list\033[0m\n");
	/*debug*/printf("\033[90m1:[0]env_list && [1]export_list\033[0m\n");
	/*debug*/printf("\033[90m2:[1]env_list && [1]export_list\033[0m\n");
	/*debug*/printf("\033[103m_____vars_list:_____\033[0m\n");
	while (tmp != NULL)
	{
		/*debug*/printf("%s:\033[93m%s\033[0m. export_id[\033[93m%d\033[0m]\n", (char*)tmp->env, (char*)tmp->content, tmp->exported);
		tmp = tmp->next;
	}
	/*debug*/printf("\033[90m_________end_________\033[0m\n");
}
