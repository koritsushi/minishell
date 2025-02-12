/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:20:44 by mliyuan           #+#    #+#             */
/*   Updated: 2025/02/12 09:09:44 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "signals.h"
# include <errno.h>
# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/*for debug purposes only*/
void	debug_print(char **res);


#endif