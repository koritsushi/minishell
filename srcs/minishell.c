/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:12:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/03/11 15:20:42 by hsim             ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	char	*text;
	// char	*input;
	t_token	lst;

	if (argc > 1 && ft_strncmp(argv[0], "minishell", 9) != 0)
		exit(127);
	set_signal_action();
	block_signal(SIGQUIT);
	lst.vars = NULL;
	while (1)
	{
		text = readline("\033[34mminishell ˚𓆝 ⋆｡𓆟 ⋆｡𓆞˚ 𓇼  > \033[0m");
		// text = input;
		if (text == NULL)
			exit(ENOMEM);
		if (*text)
			add_history(text);
		if (ft_strncmp(text, "exit", 4) == 0)
		{
			ft_putstr_fd("\033[32mminishell exited!\033[0m\n", 1);
			break ;
		}
		if (ft_strncmp(text, "print", 5) == 0)
		{
			printf("\033[103m_____vars_list:_____\033[0m\n");
			if (lst.vars && lst.vars->content)
				debug_print_lst(lst.vars);
		}
		/*lexing & get_vars*/
		else if (*text && check_syntax(text))
		{
			get_variable(&lst.vars, text);
			if (lst.vars && lst.vars->content)
				debug_print_lst(lst.vars);
			if (get_cmd_line(text, &lst))
				free_all(&lst);
		}
		free(text);
		// free(input);
	}
	free(text);
	if (lst.vars && lst.vars->content)
		ft_lstclear(&lst.vars, free);
	return (0);
}

