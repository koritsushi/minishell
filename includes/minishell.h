/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:20:44 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/01 08:40:54 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "parsing.h"
# include "token.h"
# include "expansion.h"
# include "signals.h"
# include <errno.h>
# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	// int				export_id; //exported;
	int				exported;
	char			*env;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	unsigned char	*datatype; //datatype
	char			**data; //malloc string: "infile" "cmd1 -f -g -h" "cmd2" "outfile"
	t_env			*vars;
	// t_list			*vars;
}	t_token;

/*______________for debug purposes only______________*/
void	debug_print(char **res);

/*______________modified linked_lst function from libft______________*/
t_env	*ft_lstlast_sh(t_env *lst);
t_env	*ft_lstnew_sh(void *content);
void	ft_lstadd_back_sh(t_env **lst, t_env *new);
void	ft_lstdelone_sh(t_env *lst, void (*del)(void*));
void	ft_lstclear_sh(t_env **lst, void (*del)(void*));

/*______________free memory allocations______________*/
void	free_chr_ptr(void **ptr);


#endif