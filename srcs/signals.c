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

// Blocks the specified signal
// sigset_t sigset 	-> Set of signals to block
// sigemptyset 		-> Initialize set to 0
// sigaddset 		-> Add the signal to the set
// -> Add the signals in the set to the process' blocked signals
// sigprocmask
// void	block_signal(int signal)
// {
// 	sigset_t	sigset;

// 	sigemptyset(&sigset);
// 	sigaddset(&sigset, signal);
// 	sigprocmask(SIG_BLOCK, &sigset, NULL);
// 	if (signal == SIGINT)
// 		printf("\e[36mSIGINT (ctrl-c) blocked.\e[0m\n");
// 	else if (signal == SIGQUIT)
// 		printf("\e[36mSIGQUIT (ctrl-\\) blocked.\e[0m\n");
// }

// Unblocks the given signal
// -> Set of signals to unblock
// sigset_t sigset
// -> Initialize the set to 0
// sigemptyset
// -> Add the signal to the set
// sigaddset(&sigset, signal)
// -> Remove set signals from the process' blocked signals
// sigprocmask(SIG_UNBLOCK, &sigset, NULL)
// void	unblock_signal(int signal)
// {
// 	sigset_t	sigset;

// 	sigemptyset(&sigset);
// 	sigaddset(&sigset, signal);
// 	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
// 	if (signal == SIGINT)
// 		printf("\e[36mSIGINT (ctrl-c) blocked.\e[0m\n");
// 	else if (signal == SIGQUIT)
// 		printf("\e[36mSIGQUIT (ctrl-\\) unblocked.\e[0m\n");
// }

// SIGINT && SIGQUIT signal handler
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

// Set all of the structure's bits to 0 to avoid errors
// -> relating to uninitialized variables
// bzero(&act, sizeof(act)); 		
// -> Set the signal handler as the default action 
// act.sa_handler = &sigint_handler;
// -> Apply the action in the structure to the
// ct.sa_handler = &sigint_handler;
// SIGINT signal (ctrl-c)
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
