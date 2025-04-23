/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:20:44 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/23 11:11:42 by mliyuan          ###   ########.fr       */
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

typedef struct s_exec
{
	int			pipes[1024][2];
	int			infile_fd;
	int			outfile_fd;
	int			here_doc;
	char		**cmd_paths;
	char		***cmd_args;
	int			cmd_count;
	int			index;
}				t_exec;

typedef struct s_env
{
	int				exported;
	char			*env;
	char			*content;
	struct s_env 	*next;
}					t_env;

typedef struct s_ms
{
	t_exec		*exec;
	t_env		*env_var;
}					t_ms;

#endif