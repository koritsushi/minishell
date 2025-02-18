/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:20:44 by mliyuan           #+#    #+#             */
/*   Updated: 2025/02/18 22:08:39 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	common header file such as
	# include <unistd.h>
	# include <limits.h>
	# include <stdlib.h>
	# include <stdio.h>
	# include <stdarg.h>
	# include <stdint.h>
	are in libft header file
*/
#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <strings.h>
# include "../libft/libft.h"
# include "execution.h"
# include "builtins.h"
# include "env.h"
# include "signals.h"

#endif