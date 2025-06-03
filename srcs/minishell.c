/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:12:37 by mliyuan           #+#    #+#             */
/*   Updated: 2025/06/03 12:23:07 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_signal = 0;

void	remove_redir_quote(t_token *lst)
{
	int	i;

	i = -1;
	while (lst->data[++i])
	{
		if (lst->datatype[i] != WORD && lst->datatype[i] != HEREDOC)
			quote_removal(&lst->data[i]);
	}
}

/*
 * helper function for minishell main
 * starts all cmd
 * lexing, get_vars, execution function call
 */
void	start_cmd(char *text, t_ms *data)
{
	if (get_cmd_line(text, &data->lst, data->env_var, data->exec.exit_code))
	{
		get_variable(&data->env_var, data->lst, text);
		add_filler_cmd(&data->lst);
		remove_redir_quote(&data->lst);
		execute_functions(data, data->lst);
		free_exec(&data->exec);
		free_parsing(&data->lst);
	}
}

static int	check_ifs(char *text, t_ms *data)
{
	if (text == NULL)
		return (ft_perror_fd("\e[0;31mlogout\e[0;0m\n", 1, 0));
	if (g_signal == 130)
	{
		data->exec.exit_code = g_signal;
		g_signal = 0;
	}
	if (*text)
		add_history(text);
	if (*text && check_syntax(text))
		start_cmd(text, data);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	data;
	char	*text;

	if (argc > 1 && ft_strncmp(argv[0], "minishell", 9) != 0)
		exit(1);
	set_signal_action(1);
	data.env_var = NULL;
	data.exec.exit_code = 0;
	env_init(&data.env_var, env);
	while (1)
	{
		exec_init(&data.exec);
		text = readline("\033[34mminishell ˚𓆝 ⋆｡𓆟 ⋆｡𓆞˚ 𓇼  > \033[0m");
		if (!check_ifs(text, &data))
			break ;
		free(text);
	}
	free(text);
	rl_clear_history();
	if (data.env_var && data.env_var->content)
		ft_lstclear_sh(&data.env_var, free);
	return (0);
}
