/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:47:44 by mliyuan           #+#    #+#             */
/*   Updated: 2025/02/18 15:47:44 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "minishell.h"

typedef struct s_ms		t_ms;
typedef struct s_env	t_env;
typedef struct s_exec	t_exec;

void	msh_init(t_ms *data, char** env);
void	env_init(t_env **env_var, char **env);
void	exec_init(t_exec *exec);
void	export(t_env **env_var, t_env *lenv);
void	unset(t_env **env_var, t_env *lenv);
void	env_print(t_env **lst);
void	export_print(t_env **lst);

t_env	*ft_lstlast_sh(t_env *lst);
void	ft_lstadd_back_sh(t_env **lst, t_env *new);
void	ft_lstdelone_sh(t_env *lst, void (*del)(void*));
void	ft_lstclear_sh(t_env **lst, void (*del)(void*));
t_env	*ft_lstnew_sh(char *name, char *content, int export_id);
t_env	*ft_lstnew_env(char *name, char *content, int export_id);
#endif
