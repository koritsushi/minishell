/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_shell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:35:57 by hsim              #+#    #+#             */
/*   Updated: 2025/03/15 11:49:47 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

/*
 * child function in copy_shell_var
 * perform split checks if there are unseparated var (eg $var$var2)
 * returns 1 if true
 */
static int	has_unseparated_var(char *str, char *symbol)
{
	char	**tmp;
	int		res;
	char	*check;

	/* var=" var' "*/
	/* var=" $var "*/
	/* var=' $var '*/
	/* $var"$var" */
	res = 0;
	tmp = ft_split_shell(str, " \t\n\v\f\r");
	// /*debug*/printf("has_unseparated_var:\n");
	// /*debug*/debug_print(tmp);

	check = tmp[0] + 1;
	while (check && check[0] && !is_target(" \t\n\v\f\r", check[0]) && !res)
	{
		if (is_target("\'\"$", check[0]))
		{
			*symbol = check[0];
			res = 1;
		}
		check++;
	}
	free_chr_ptr((void **)tmp);
	return (res);
}

/*
 * child helper function in copy_shell_var
 * updates str pointer to point to the next available word/var
 */
static char	*next_available_var(char *str)
{
	char	symbol;

	symbol = '$';
	if (has_unseparated_var(str, &symbol)) // if $var$var1, $var"hello" $var"hello$var1"
		str = ft_strchr(str + 1, symbol);
	else
	{
		str = skip_if_symbol(str, str[0], symbol);
		if (str)
			str -= 1;
	}
	return (str);
}

// 23 lines!
/*
 * child helper function in check_replace_var
 * copy string from str & src to dest
 */
char	*copy_shell_var(char *str, char *dest, char *src)
{
	int		i;
	int		flag;

	if (!str)
		return (0);
	i = 0;
	flag = 0;
	while (str && str[0])
	{
		if (str[0] == '\'')
			flag = 1;
		if (str[0] == '$' && !flag)
		{
			i += ft_strlcpy(&dest[i], src, ft_strlen(src) + 1);
			str = next_available_var(str);
			flag = 1;
			/*debug*/printf("skips:\033[92m%s\033[0m\n", str);
		}
		else
			dest[i++] = *str++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
 * child function in check_shell_var
 * mallocs new string, copy over from old string to new string
 * free & reassign *cmd_line to point to the new allocated string
 * src = content to copy over
 */
void	check_replace_var(char **cmd_line, char *name, char *src)
{
	int		i;
	char	*tmp;

	/*debug*/printf("str:%s. %zu\n", *cmd_line, ft_strlen(*cmd_line));
	/*debug*/printf("str:%lu, name:%lu, start:%lu\n malloc:%lu\n", ft_strlen(*cmd_line), ft_strlen(name), ft_strlen(src), ft_strlen(*cmd_line) - ft_strlen(name) + ft_strlen(src));
	/*debug*/printf("check_replace_var:same! start:%s\n", src);	
	i = ft_strlen(*cmd_line);
	malloc_chr_ptr(&tmp, i - ft_strlen(name) + ft_strlen(src));
	copy_shell_var(*cmd_line, tmp, src);
	// /*debug*/printf("res:%s, %d\n", tmp, i);
	free(*cmd_line);
	*cmd_line = tmp;
}

// 24 lines!
/*
 * child function in shell_var_expansion, checks if $var entry exist in t_list
 * yes: copy over the content to str
 * no : replace $var with ' ' spaces
 */
void	check_shell_var(t_list *vars, char *name, char **cmd_line)
{
	char	**tmp;
	int		flag;
	char	*start;

	flag = 0;
	while (vars && !flag)
	{
		tmp = ft_split_shell(vars->content, "=");
		// /*debug*/printf("check_replace_dup name:%s, %s\n", tmp[0], name);
		if (ft_strlen(tmp[0]) == ft_strlen(name) && \
			ft_strncmp(vars->content, name, ft_strlen(name)) == 0)
		{
			start = ft_strchr(vars->content, '=') + 1;
			check_replace_var(cmd_line, name, start);
			flag = 1;
		}
		free_chr_ptr((void **)tmp);
		vars = vars->next;
	}
	if (!flag)
	{
		start = ft_strchr(*cmd_line, '$');
		while (start && start[0] && !is_target(" \t\n\v\f\r", start[0]))
			*start++ = ' ';
		/*debug*/printf("notfound! updated:%s.\n", *cmd_line);
	}
}

