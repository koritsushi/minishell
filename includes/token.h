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
	char			**data; //malloc string
	// struct s_token	*next;
} t_token;


char	**ft_split_shell(char *str, char *set);
int		is_target(char *str, char c);

void	get_cmd_line(char *str, t_token *lst);
void	copy_cmd(char **dest, char *src, int *start, int len);
void	identify_op(char *str, unsigned char *datatype);
int		is_all_op(char *set, char *str);

int		allocate_str(char **res, char **data, int i);


/* free memory allocations*/
void	free_all(t_token *lst);

/*debug testing only*/
int	count_str(char *str, char *set);
int	count_chr(char *str, char *set, int *ptr);
// int	has_pipes(char *set, char **res);
int	if_target_exist(char *set, char *str);


#endif