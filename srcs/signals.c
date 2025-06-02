/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:56:49 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/09 18:56:49 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

extern int	g_signal;

/* SIGINT && SIGQUIT signal handler */
void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putstr_fd("\n\033[34mminishell ˚𓆝 ⋆｡𓆟 ⋆｡𓆞˚ 𓇼  > \033[0m", 1);
		g_signal = 130;
		return ;
	}
}

void	default_signal_action(struct sigaction act)
{
	act.sa_handler = &signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	ignore_signal_action(struct sigaction act)
{
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	reset_signal_action(struct sigaction act)
{
	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

/*
 * Set all of the structure's bits to 0 to avoid errors
 * -> relating to uninitialized variables
 * bzero(&act, sizeof(act)); 		
 * -> Set the signal handler as the default action 
 * act.sa_handler = &sigint_handler;
 * -> Apply the action in the structure to the
 * act.sa_handler = &sigint_handler;
 * SIGINT signal (ctrl-c)
 */
void	set_signal_action(int code)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	if (code == 1)
		default_signal_action(act);
	else if (code == 2)
		ignore_signal_action(act);
	else if (code == 3)
	 	reset_signal_action(act);
	else 
		set_heredoc_signal_handler(act);
}
