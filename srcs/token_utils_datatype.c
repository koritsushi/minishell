/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_datatype.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 07:55:00 by hsim              #+#    #+#             */
/*   Updated: 2025/02/25 07:56:28 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/token.h"

/* scans input and assigns datatype according to operator sign */
void	assign_datatype(unsigned char *datatype, char **res)
{
	int	x;
	int	i;
}

// void	assign_datatype(t_token *lst, char **res)
// {
// 	int	x;
// 	int	i;

// 	x = 0;
// 	i = 0;
// 	identify_op(res[i], &lst->datatype[x++]);
// 	while (res[i])
// 	{
// 		while (res[i])// && !is_target("<>|", res[i][0]))
// 		{
// 			if (is_target("<>|", res[i][0]) && res[i][1] == '\0')
// 				break ;
// 			i++;
// 		}
// 		if (res[i])
// 			identify_op(res[i++], &lst->datatype[x++]);
// 		else
// 			lst->datatype[x] = END;
// 	}
// }