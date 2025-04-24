/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:59 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/24 20:48:06 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define PATHMX 4096
# include "minishell.h"

char	*getpwd(void);
int		ft_pwd(void);
int		ft_cd(t_env **lst, char *dir);
int		ft_echo(int argc, char **args);

#endif