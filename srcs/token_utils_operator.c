/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_operator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:09:44 by hsim              #+#    #+#             */
/*   Updated: 2025/02/12 19:21:22 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/* child function in identify_op, use to check if infile < symbol is valid */
static void	identify_op_infile(unsigned char *datatype, char *str)
{
	if (str[1] && is_target("<", str[1]) && str[2] == '\0')
		*datatype = HEREDOC;
	else if (str[1] == '\0' && is_target("<", str[0]))
		*datatype = INFILE;
	else
		*datatype = ERR;
}

/* child function in identify_op, use to check if outfile > symbol is valid */
static void	identify_op_outfile(unsigned char *datatype, char *str)
{
	if (str[1] && is_target(">", str[1]) && str[2] == '\0')
		*datatype = OUTFILE_A;
	else if (str[1] == '\0' && is_target(">", str[0]))
		*datatype = OUTFILE;
	else
		*datatype = ERR;
}

void	identify_op(char *str, unsigned char *datatype)
{
    if (!str || !str[0])
        return ;
	if (str[0] && is_target("<", str[0]))
		identify_op_infile(datatype, str);
	else if (str[0] && is_target(">", str[0]))
		identify_op_outfile(datatype, str);
	else
		*datatype = WORD;
}
