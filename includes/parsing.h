/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:55:30 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/11 13:55:30 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   does syntax checking for general & variable assignment ($var)
 *   saves valid variable assignment ($var) to linked list
 * ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

typedef struct s_env	t_env;

/*__________functions for syntax error checks__________*/
int		check_syntax(char *str);
int		check_var_syntax(char *str);//, int *flag);
char	*skip_if_quote(char *str, char symbol, int flag);
char	*skip_redirs(char *str);

/*__________functions to extract variable assignments__________*/
int		get_variable(t_env **vars, char *str, int exit_status);
int		get_var_name(char **dest, char *str);
int		is_valid_var_name(char **str, int export_id);
void	replace_var_space(char *str);
int		count_malloc_vars(char *str);
void	copy_vars(char *dest, char *src, int len);
void	extract_vars(t_env **vars, char *str, int export_id);
int		check_replace_dup(t_env *vars, char *name, char *new, int export_id);
int		valid_export_keyword(char *str, int flag);

/*__________functions to clear variable assignments__________*/
char	*overwrite_export_line(char *str);


#endif