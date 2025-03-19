/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:59 by mliyuan           #+#    #+#             */
/*   Updated: 2025/03/19 19:49:54 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define PATHMX 4096
# include "minishell.h"

char	*getpwd(void);
void	printpath(void);
void	chgwd(char *dir);
void	echo(int argc, char **args);

#endif