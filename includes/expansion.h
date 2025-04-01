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
# include "includes/minishell.h"

typedef struct s_env	t_env;

int		cmd_expansion(char **lst_data, t_env *vars);
void	shell_var_expansion(char **cmd_line, t_env *vars);
void	check_shell_var(t_env *vars, char *name, char **cmd_line, char *str);

int		has_valid_brace_content(char *str);
int		is_valid_brace_start(char *str);

int		get_expansion_count(char *str);
void	perform_brace_expansion(char **cmd_line, int malloc_size);
char	*copy_brace_expansion(char *src, char *dest, int *x, int malloc_size);



#endif