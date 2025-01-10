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

#include "includes/minishell.h"

/*
	Set all of the structure's bits to 0 to avoid errors
	bzero(&act, sizeof(act)); 			-> relating to uninitialized variables
	act.sa_handler = &sigint_handler; 	-> Set the signal handler as the default action
	ct.sa_handler = &sigint_handler; 	-> Apply the action in the structure to the
	SIGINT signal (ctrl-c)
*/
void	set_signal_action(void)
{
	struct	sigaction act;
	
	bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
}

/*
	Blocks the specified signal
	sigset_t sigset 	-> Set of signals to block
	sigemptyset 		-> Initialize set to 0
	sigaddset 		-> Add the signal to the set
	sigprocmask		-> Add the signals in the set to the process' blocked signals
*/
void	block_signal(int signal)
{
	
	sigset_t sigset;

	
	sigemptyset(&sigset);
	
	sigaddset(&sigset, signal);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT (ctrl-\\) blocked.\e[0m\n");
}

/*
	Unblocks the given signal
	sigset_t sigset 						-> Set of signals to unblock
	sigemptyset								-> Initialize the set to 0
	sigaddset(&sigset, signal)				-> Add the signal to the set
	sigprocmask(SIG_UNBLOCK, &sigset, NULL) -> Remove set signals from the process' blocked signals
*/ 
void	unblock_signal(int signal)
{
	
	sigset_t sigset;

	
	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT (ctrl-\\) unblocked.\e[0m\n");
}

// SIGINT signal handler
//	signal != SIGINT		-> Blocks other SIGINT signals to protect the global
//	g_unblock_sigquit = 1;	->	variable during access
void	sigint_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	block_signal(SIGINT);
	g_unblock_sigquit = 1;
	unblock_signal(SIGINT);
}