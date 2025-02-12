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

enum	e_var
{
	OP = 0,
	CHR = 1
};

typedef struct s_token
{
	unsigned char	*datatype; //datatype
	char			**data; //malloc string
	// struct s_token	*next;
} t_token;


void	get_cmd_line(char *str, t_token *lst);
char	**ft_split_shell(char *str, char *set);
int		is_target(char *str, char c);


/*debug testing only*/
int	count_str(char *str, char *set);
int	count_chr(char *str, char *set, int *ptr);



#endif