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

int		check_syntax(char *str);
char	*skip_if_quote(char *str, char symbol);
char	*skip_redirs(char *str);

/*__________functions to extract variable assignments__________*/
int		get_variable(t_list **vars, char *str);
void	get_var_name(char **dest, char *str);
void	replace_var_space(char *str);


#endif