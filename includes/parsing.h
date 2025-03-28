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

typedef struct s_env
{
	int				exported;
	char			*env;
	char			*content;
	struct s_env	*next;
}	t_env;


/*__________functions for syntax error checks__________*/
int		check_syntax(char *str);
int		check_var_syntax(char *str, int *flag);
char	*skip_if_quote(char *str, char symbol, int flag);
char	*skip_redirs(char *str);
int		has_mix_redirs(char *str);

/*__________functions to extract variable assignments__________*/
int		get_variable(t_list **vars, char *str);
int 	get_var_name(char **dest, char *str);
void	replace_var_space(char *str);
void	extract_vars(t_list **vars, char *str, int export_id);

/*__________functions to clear variable assignments__________*/
char	*overwrite_export_line(char *str);


#endif