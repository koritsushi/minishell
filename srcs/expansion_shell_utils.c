/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_shell_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:21:00 by hsim              #+#    #+#             */
/*   Updated: 2025/04/11 11:02:56 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   utils function for expanding/copying shell var ($var) properly
 * ************************************************************************* */

#include "includes/expansion.h"

/*
 * child function in next_available_var
 * perform split checks if there are unseparated var (eg $var$var2)
 * returns 1 if true
 */
// static int	has_unseparated_var(char *str, char *symbol)
// {
// 	char	**tmp;
// 	int		res;
// 	char	*check;

// 	/* var=" var' "*/
// 	/* var=" $var "*/
// 	/* var=' $var '*/
// 	/* $var"$var" */
// 	res = 0;
// 	tmp = ft_split_shell(str, " \t\n\v\f\r");
// 	// /*debug*/printf("has_unseparated_var:\n");
// 	// /*debug*/debug_print(tmp);

// 	check = tmp[0] + 1;
// 	while (check && check[0] && !is_target(" \t\n\v\f\r", check[0]) && !res)
// 	{
// 		if (is_target("\'\"$", check[0]))
// 		{
// 			*symbol = check[0];
// 			res = 1;
// 		}
// 		check++;
// 	}
// 	free_chr_ptr((void **)tmp);
// 	return (res);
// }

/*
 * child helper function in copy_shell_var
 * updates str pointer to point to the next available word/var
 */
// static char	*next_available_var(char *str)
// {
// 	char	symbol;

// 	symbol = '$';
// 	if (has_unseparated_var(str, &symbol)) // if $var$var1, $var"hello" $var"hello$var1"
// 		str = ft_strchr(str + 1, symbol);
// 	else
// 	{
// 		str = skip_if_symbol(str, str[0], symbol);
// 		if (str)
// 			str -= 1;
// 	}
// 	return (str);
// }

/*
 * child helper function in copy_shell_var
 * updates flag status according to symbol
 * main_flag will be the one values altered
 * target=str[0],  symbol=single or double quote
 */
static void	update_flag_status(char target, char symbol, int *main_flag, int sub_flag)
{
	if (!sub_flag && !(*main_flag) && target == symbol)
		(*main_flag) = 1;
	else if ((*main_flag) == 1 && target == symbol)
		(*main_flag) = 0;
}

// 24 lines!
/*
 * child helper function in check_replace_var
 * str = *cmd_line, src = expanded_content (eg var=src)
 * copy string from str & src to dest
 * only expands the 1st $var set, copies & return the rest, repeat
 */
char	*copy_shell_var(char *str, char *dest, char *src, int var_name_len)
{
	int		i;
	int		flag;
	int		double_quote;

	if (!str)
		return (0);
	i = 0;
	flag = 0;
	double_quote = 0;
	while (str && str[0])
	{
		update_flag_status(str[0], '\"', &double_quote, flag);
		update_flag_status(str[0], '\'', &flag, double_quote);
		if (!flag && str[0] == '$' && str[1] != '$')
		{
			i += ft_strlcpy(&dest[i], src, ft_strlen(src) + 1);
			// str = next_available_var(str);
			str += var_name_len;
			flag = 2;
			/*debug*/printf("copy_shell_var:skips:\033[92m%s\033[0m\n", str);
		}
		else
			dest[i++] = *str++;
		// /*debug*/printf("copy_shell_var:%s, %d, flag:%d\n", dest, i, flag);
	}
	dest[i] = '\0';
	return (dest);
}


// char	*copy_shell_var(char *dest, char *src, int var_name_len, char *symbol)
// {
// 	int		i;
// 	int		flag;
// 	int		double_quote;

// 	if (!src)
// 		return (0);

// 	if (symbol = '\"')
// 		double_quote = 1;

// 	i = 0;
// 	flag = 0;
// 	double_quote = 0;
// 	while (str && str[0])
// 	{
// 		update_flag_quote
// 		update_flag_status(str[0], '\"', &double_quote, flag);
// 		update_flag_status(str[0], '\'', &flag, double_quote);
// 		if (!flag && str[0] == '$' && str[1] != '$')
// 		{
// 			i += ft_strlcpy(&dest[i], src, ft_strlen(src) + 1);
// 			// str = next_available_var(str);
// 			str += var_name_len;
// 			flag = 2;
// 			/*debug*/printf("copy_shell_var:skips:\033[92m%s\033[0m\n", str);
// 		}
// 		else
// 			dest[i++] = *str++;
// 		// /*debug*/printf("copy_shell_var:%s, %d, flag:%d\n", dest, i, flag);
// 	}
	
// 	return (dest);
// }
