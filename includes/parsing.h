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

#ifndef PARSING_H
# define PARSING_H
# include "includes/minishell.h"

// typedef struct s_vars
// {
// 	void			*data;	// char *content vars=123 va
// 	struct s_vars	*next;
// }	t_vars;

int		check_syntax(char *str);
char	*skip_if_quote(char *str, char symbol);


int		get_variable(t_list **vars, char *str);
void	get_var_name(char **dest, char *str);


#endif