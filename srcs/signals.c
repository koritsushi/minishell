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
		ft_putstr_fd("\n\033[34mminishell ˚𓆝 ⋆｡𓆟 ⋆｡𓆞˚ 𓇼  > \033[0m", 1);
		g_signal = 130;
		return ;
	}
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("\033[34mminishell ˚𓆝 ⋆｡𓆟 ⋆｡𓆞˚ 𓇼  > \033[0m", 1);
		return ;
	}
}

void	default_signal_action(struct sigaction df_act, struct sigaction ign_act)
{
	df_act.sa_handler = &signal_handler;
	sigemptyset(&df_act.sa_mask);
	if (ign_act.sa_flags == 0)
	{
		sigaction(SIGINT, &df_act, NULL);
		sigaction(SIGQUIT, &df_act, NULL);
	}
	else
	{
		sigaction(SIGINT, &df_act, &ign_act);
		sigaction(SIGQUIT, &df_act, &ign_act);
	}
}

void	ignore_signal_action(struct sigaction df_act, struct sigaction ign_act)
{
	ign_act.sa_handler = SIG_IGN;
	sigemptyset(&ign_act.sa_mask);
	sigaction(SIGINT, &ign_act, &df_act);
	sigaction(SIGQUIT, &ign_act, &df_act);
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
	struct sigaction	df_act;
	struct sigaction	ign_act;

	ft_bzero(&df_act, sizeof(df_act));
	ft_bzero(&ign_act, sizeof(ign_act));
	ign_act.sa_flags = 0;
	if (code == 1)
		default_signal_action(df_act, ign_act);
	else if (code == 2)
		ignore_signal_action(df_act, ign_act);
}
