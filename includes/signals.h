/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:18:05 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/11 13:18:05 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include "minishell.h"
# include <signal.h>

//void	block_signal(int signal);
//void	unblock_signal(int signal);
void	signal_handler(int signal);
void	set_signal_action(int code);
void	set_heredoc_signal_handler(struct sigaction act);

#endif