/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:29:17 by mliyuan           #+#    #+#             */
/*   Updated: 2025/01/11 14:17:40 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexical.h"

/*
	scan and tokenize all of these characters
	' ' ' single quote
	' " ' double quote
	' < ' redirect input
	' > ' redirect output
	" << " delimiter
	" >> " redirect output append mode
	' | ' pipe
	' $ ' environment variables 
*/