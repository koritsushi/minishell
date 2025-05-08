/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:54:40 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/11 13:54:40 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "minishell.h"

typedef struct s_env	t_env;

int		cmd_expansion(char **lst_data, t_env *vars, int exit_status);

/*__________functions for shell var expansion__________*/

// void	shell_var_expansion(char **cmd_line, t_env *vars, int exit_status);
void	shell_var_expansion(char **cmd_line, t_env *vars, int exit_status);
char	*expand_shell_var(t_env *vars, char **cmd_line, char *str, int *index);
// char	*expand_shell_var(t_env *vars, char **cmd_line, char *str);
// char	*copy_shell_var(char *str, char *dest, char *src, int var_name_len);


/* __________functions for shell exit status expansion__________*/

char	*expand_exit_status(char **cmd_line, int exit_status, int *index);


/*__________functions for brace expansion__________*/

int		has_valid_brace_content(char *str);
int		is_valid_brace_start(char *str);
int		get_expansion_count(char *str);
char	*perform_brace_expansion(char *str, char **cmd_line, int *x);
char	*copy_brace_expansion(char *src, char *dest, int *x, int malloc_size);
void	update_flag_quote(char *target, char *symbol, int *flag_quote);


/* __________functions for quote removal expansion__________*/

int		count_malloc_quote_removal(char *str);
void	expand_quote_removal(char *src, char *dest);
void	quote_removal(char **cmd_line);


#endif