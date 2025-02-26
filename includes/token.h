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
# include "includes/minishell.h"

enum e_type
{
	WORD,
	INFILE,		// <
	HEREDOC,	// <<
	OUTFILE,	// >
	OUTFILE_A,	// >>
	PIPE,		// |
	ENV,		// $
	ERR,		// error
	END
};

enum e_utils
{
	IN = 0,
	OUT = 1
};

typedef struct s_token
{
	unsigned char	*datatype; //datatype
	char			**data; //malloc string: "infile" "cmd1 -f -g -h" "cmd2" "outfile"
	// struct s_token	*next;
} t_token;

typedef struct	s_env
{
	char 			*data;
	struct s_env	*next;
} t_env;


char	**ft_split_shell(char *str, char *set);

/* ---------------------for_checking---------------------- */
int		is_target(char *str, char c);
int		has_more_str(char *str, char *set);
int		has_more_str_all(char **str, char *set);

void	get_cmd_line(char *str, t_token *lst);
// void	copy_cmd(char **dest, char *src, int *start, int len);
// void	identify_op(char *str, unsigned char *datatype);
// int		is_all_op(char *set, char *str);

/* -------------------count_&_mallocs---------------------- */
int		count_str_array(char **res);
int		get_malloc_size(char **res, char **infile);
int		allocate_str(char **dest, char *str);
int		allocate_cmd_tail(char **dest, char **outfile, char c);
int		init_token_list(t_token *lst, int size);

char	*skip_if_symbol(char *str, char c, char symbol);
// char	*skip_if_symbol(char *str, char *set, char c, char symbol);
char	*skip_spaces(char *str, char *set);

void	extract_infile(char **lst_data, char **res, char **infile);
void	extract_cmd_head(char **lst_data, char **res, char **infile);



char	*truncate_input(char *str);


/* -----------------free_memory_allocations----------------- */
void	free_all(t_token *lst);
void	free_multiple_ptr(int x, ...);


/*debug testing only*/
int		count_str(char *str, char *set);
int		count_chr(char *str, char *set, int *ptr);
int		if_target_exist(char *set, char *str);
char	*truncate_last_infile(char *str);
char	*search_rstr(char *str, char c, int len);
void	debug_print(char **res);


#endif