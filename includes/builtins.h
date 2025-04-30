/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:59 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/30 09:29:07 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define PATHMX 4096
# include "minishell.h"

typedef struct s_env	t_env;

char	*getpwd(void);
int		ft_pwd(void);
int		ft_cd(t_env **lst, char *dir);
int		ft_echo(int argc, char **args);
void	ft_lst_replace_if(t_env *lst, char *name, char *content);

#endif