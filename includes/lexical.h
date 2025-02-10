/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:54:40 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/11 13:54:40 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_H
# define LEXICAL_H
# include "includes/minishell.h"

enum e_datatype
{
	WORD,		/* ascii 32-126, except ' "  */
	NUM,		/* all digits */
	OP,			/* all operators in general */
	PIPE,		/* | */

	/*---------------subs of WORD---------------*/
	VAR,		/* starts with $, can be $<ID> or $? */
	ID,			/* str[0] MUST start with alphabet, next can be alnum*/
	FIL,		/* can start with digit or special char */

	/*---------------subs of OP---------------*/
	REDIR_OP,	/* such as   < >  <<  >>  */
	CONTR_OP,	/* such as   && || PIPE ( ) */
	REL_OP,		/* such as   ==  <  >  =!=   =>   =<  */
	ARITH_OP,	/* such as  = :  +  -  *  / %  */

	DELIM,		/* such as  . (  ) , { } ; [ ] */
	UNDEF,		/* undefined */
	EOT			/* end of token */
};

#endif