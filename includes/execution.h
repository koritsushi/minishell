/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:20:02 by mliyuan           #+#    #+#             */
/*   Updated: 2025/02/18 17:20:02 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H
# include "minishell.h"
# define READ 0
# define WRITE 1

typedef struct s_ms		t_ms;
typedef struct s_exec	t_exec;
typedef struct s_token	t_token;
typedef struct s_env	t_env;

void	ft_execs_init(t_ms *data, t_token lst);
void	ft_init_pipe(t_ms *data, t_token lst);
char	**ft_envp(t_env **lst);

//execution_cmd.c functions
char	**ft_get_path(char **envp);
char	**ft_format_path(char **path, char *format);
char	***ft_split_cmd(t_exec *exec, char **argv);
void	ft_cmdpath(t_exec *exec, char **path);
void	ft_cmdpath_error(t_ms *data, char *cmd, char **path);
#endif