/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:29:17 by mliyuan           #+#    #+#             */
/*   Updated: 2025/03/03 20:55:22 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

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
