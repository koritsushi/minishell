/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:20:44 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/02 17:48:29 by mliyuan          ###   ########.fr       */
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
//libft header
# include "../libft/libft.h"
//minishell headers
# include "parsing.h"
# include "token.h"
# include "expansion.h"
# include "execution.h"
# include "builtins.h"
# include "env.h"
# include "signals.h"
//c library
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_exec
{
	int				pipes[1024][2];
	int				infile_fd;
	int				outfile_fd;
	int				here_doc;
	char			**cmd_paths;
	char			***cmd_args;
	int				cmd_count;
	int				index;
	unsigned char	exit_code;
}	t_exec;

typedef struct s_env
{
	int				exported;
	char			*env;
	char			*content;
	struct s_env 	*next;
}	t_env;

typedef struct s_ms
{
	t_exec		exec;
	t_env		*env_var;
}	t_ms;

typedef struct s_token
{
	unsigned char	*datatype;
	char			**data; //string: "infile" "cmd1 -f -g -h" "cmd2" "outfile"
}	t_token;

/*__________for debug purposes only, can remove during eval__________*/
void	debug_print(char **res);
void	debug_print_var_lst(t_env *lst);
void	debug_print_cmd_line(t_token *lst);
void	debug_print_cd(void);


/*___________________helper function executing cmd___________________*/
void	execute_functions(t_ms *data, t_token lst);
int		execute_built_in(t_ms *data, char *argv);

// void	execute_built_in(t_ms data, t_env *env, int argc, char **argv);

/*______________modified linked_lst function from libft______________*/
t_env	*ft_lstlast_sh(t_env *lst);
t_env	*ft_lstnew_sh(char *name, char *content, int export_id);
void	ft_lstadd_back_sh(t_env **lst, t_env *new);
void	ft_lstdelone_sh(t_env *lst, void (*del)(void*));
void	ft_lstclear_sh(t_env **lst, void (*del)(void*));

/*______________________free memory allocations______________________*/
void	free_chr_ptr(void **ptr);

#endif