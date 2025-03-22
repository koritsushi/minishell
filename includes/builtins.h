/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:59 by mliyuan           #+#    #+#             */
/*   Updated: 2025/03/21 18:31:02 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define PATHMX 4096
# include "minishell.h"

char	*getpwd(void);
int		ft_pwd(void);
int		ft_cd(char *dir);
int		ft_echo(int argc, char **args);

#endif