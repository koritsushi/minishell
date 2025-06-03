/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:59 by mliyuan           #+#    #+#             */
/*   Updated: 2025/06/03 11:18:28 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define PATHMX 4096
# include "minishell.h"

typedef struct s_env	t_env;
typedef struct s_ms		t_ms;

char	*getpwd(void);
int		ft_pwd(void);
int		ft_cd(t_env **lst, char *dir);
int		ft_echo(char **args);
void	ft_exit(t_ms *data, char **argv);

void	ft_lst_replace_if(t_env *lst, char *name, char *content);
char	*expand_relative_path(char *str, char *curr_dir);

#endif