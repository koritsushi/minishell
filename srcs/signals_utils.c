/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:44:28 by mliyuan           #+#    #+#             */
/*   Updated: 2025/06/02 22:04:54 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

extern int	g_signal;

void	heredoc_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 130;
		write(1, "\n", 1);
		exit(130);
	}
}

void	set_heredoc_signal_handler(struct sigaction act)
{
	sigemptyset(&act.sa_mask);
	act.sa_handler = &heredoc_signal_handler;
	sigaction(SIGINT, &act, NULL);
}