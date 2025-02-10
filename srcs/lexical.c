/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:29:17 by mliyuan           #+#    #+#             */
/*   Updated: 2025/02/07 11:28:20 by hsim             ###   ########.fr       */
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

// int	start_scan(char **argv)
// {
// 	ft_split() // new type of ft_split that checks for space && ascii 9 - 13
// }
