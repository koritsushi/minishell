/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:15:09 by mliyuan           #+#    #+#             */
/*   Updated: 2025/06/03 10:32:33 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

extern int	g_signal;

void	heredoc_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		close(STDIN_FILENO);
		write(1, "\n", 1);
		g_signal = 130;
		return ;
	}
}

void	heredoc_signal_action(struct sigaction act)
{
	act.sa_handler = &heredoc_signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
