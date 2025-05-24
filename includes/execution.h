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

//execution_process.c
//void	ft_execs_init(t_ms *data, t_token *lst);
void	ft_init_pipe(t_ms *data, t_token *lst);
char	**ft_cmd_init(t_ms *data, t_token *lst);
void	ft_process(t_ms *data);
char	**ft_envp(t_env **lst);

//execution_process2.c
int		lst_cmd_count(t_token *lst);
int		lst_pipe_count(t_token *lst);
int		ft_isempty(char *str);

//execution_cmd.c functions
char	**ft_get_path(char **envp);
char	**ft_format_path(char **path, char *format);
char	***ft_split_cmd(t_exec *exec, char **argv);
char	*ft_cmdpath(char **cmd_args, char **path);
void	ft_cmdpath_error(t_ms *data, char *cmd, char **path);

//execution_process.c
void	ft_execution(t_ms *data, char *cmd, char **cmd_args);
void	ft_parent_process(t_ms *data, int index);
void	ft_child_process(t_ms *data, int index);
void	close_pipe(t_ms *data, int index);

//execution_heredoc.c
void	infile_parsing_init(t_ms *data, t_token *lst);
void	outfile_parsing_init(t_ms *data, t_token *lst);

//execution_parent_process_utils.c
void	fp_process(t_ms *data, int index);
void	lp_process(t_ms *data, int index);
void	mp_process(t_ms *data, int index);

//execution_child_process_utils.c
void	fc_process(t_ms *data, int index);
void	lc_process(t_ms *data, int index);
void	mc_process(t_ms *data, int index);
#endif