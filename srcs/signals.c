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

#include "includes/signals.h"

volatile int	g_unblock_sigquit = 0;

// Set all of the structure's bits to 0 to avoid errors
// -> relating to uninitialized variables
// bzero(&act, sizeof(act)); 		
// -> Set the signal handler as the default action 
// act.sa_handler = &sigint_handler;
// -> Apply the action in the structure to the
// ct.sa_handler = &sigint_handler;
// SIGINT signal (ctrl-c)
void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
}

// Blocks the specified signal
// sigset_t sigset 	-> Set of signals to block
// sigemptyset 		-> Initialize set to 0
// sigaddset 		-> Add the signal to the set
// -> Add the signals in the set to the process' blocked signals
// sigprocmask
void	block_signal(int signal)
{	
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT (ctrl-\\) blocked.\e[0m\n");
}

// Unblocks the given signal
// -> Set of signals to unblock
// sigset_t sigset
// -> Initialize the set to 0
// sigemptyset
// -> Add the signal to the set
// sigaddset(&sigset, signal)
// -> Remove set signals from the process' blocked signals
// sigprocmask(SIG_UNBLOCK, &sigset, NULL)
void	unblock_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT (ctrl-\\) unblocked.\e[0m\n");
}

// SIGINT signal handler
// signal != SIGINT		-> Blocks other SIGINT signals to protect the global
// g_unblock_sigquit = 1;	->	variable during access
void	sigint_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	block_signal(SIGINT);
	g_unblock_sigquit = 1;
	unblock_signal(SIGINT);
}
