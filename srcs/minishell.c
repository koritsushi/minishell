/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:12:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/02 16:12:16 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		if (str[i] > 32)
			return (0);
		i++;
	}
	return (1);
}

// rmb to handle exit_status
int	main(int argc, char **argv, char **env)
{
	t_ms	data;
	char	*text;
	t_token	lst;

	if (argc > 1 && ft_strncmp(argv[0], "minishell", 9) != 0)
		exit(127);
	set_signal_action();
	//block_signal(SIGQUIT);
	//block_signal(SIGINT);
	data.env_var = NULL;
	msh_init(&data, env);
	while (1)
	{
		text = readline("\033[34mminishell ˚𓆝 ⋆｡𓆟 ⋆｡𓆞˚ 𓇼  > \033[0m");
		if (text == NULL)
		{
			ft_putstr_fd("\e[0;31mlogout\e[0;0m\n", 1);
			exit(-1);
		}
		if (*text)
			add_history(text);
		if (ft_strncmp(text, "exit", 4) == 0)
		{
			ft_putstr_fd("\033[36mminishell exited!\033[0m\n", 1);
			break ;
		}
		if (ft_strncmp(text, "print", 5) == 0)
		{
			if (data.env_var && data.env_var->content)
				debug_print_var_lst(data.env_var);
			else
				printf("\033[103m_____vars_list:_____\033[0m\n");
		}
		/*lexing & get_vars*/
		else if (*text && check_syntax(text))
		{
			get_variable(&data.env_var, text, data.exec.exit_code);
			// if (data.env_var && data.env_var->content)
			// 	debug_print_var_lst(data.env_var);
			if (get_cmd_line(text, &lst, data.env_var, data.exec.exit_code))
			{
				/*debug*/debug_print_cmd_line(&lst);
				/* execution here */
				execute_functions(&data, lst); //inject pipex inside
				// /*debug*/debug_print_cmd_line(&lst);
				free_all(&lst);
			}
		}
		free(text);
	}
	free(text);
	if (data.env_var && data.env_var->content)
		ft_lstclear_sh(&data.env_var, free);
	return (0);
}
