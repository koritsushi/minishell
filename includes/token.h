/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:56:25 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/14 19:56:25 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "minishell.h"

enum e_type
{
	WORD,
	INFILE,		// <
	HEREDOC,	// <<
	OUTFILE,	// >
	OUTFILE_A,	// >>
	PIPE,		// |
	END
};

typedef struct s_token	t_token;
typedef struct s_env	t_env;

char	**ft_split_shell(char *str, char *set);

/* ---------------------for_checking---------------------- */
int		is_target(char *str, char c);
int		has_more_str(char *str, char *set);
int		has_more_str_all(char **str, char *set);

/* -------------------extract_cmds---------------------- */
int		get_cmd_line(char *str, t_token *lst, t_env *vars, int exit_status);
void	assign_datatype(unsigned char *datatype, char **res);
void	extract_infile(char **lst_data, int *i, char *res);
void	extract_outfile(char **lst_data, char *str);
void	process_outfile(char **lst_data, int *i, \
char *cmd_tail);
void	copy_cmd_tail(char **lst_data, int *start, char **outfile);
void	add_filler_cmd(t_token *lst);

/* -------------------count_&_mallocs---------------------- */
int		count_str_array(char **res);
int		get_malloc_size(char **res);
int		allocate_str(char **dest, char *str);
int		allocate_cmd_tail(char **dest, char **outfile, char *cmd_tail);
int		init_token_list(t_token *lst, int size);
int		malloc_chr_ptr(char **dest, int len);

char	*skip_if_symbol(char *str, char c, char symbol);
char	*skip_spaces(char *str, char *set);

/* -----------------free_memory_allocations----------------- */
void	free_parsing(t_token *lst);
void	free_multiple_ptr(char **p1, char **p2, char **p3);
void	free_multiple_ptr_single(char *p1, char *p2, char *p3);

/*debug testing only*/
int		count_str(char *str, char *set);
// int		count_chr(char *str, char *set, int *ptr);
// int		if_target_exist(char *set, char *str);
// char	*truncate_last_infile(char *str);


#endif