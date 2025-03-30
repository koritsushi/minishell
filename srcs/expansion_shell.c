/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:35:57 by hsim              #+#    #+#             */
/*   Updated: 2025/03/30 08:31:11 by hsim             ###   ########.fr       */
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

// 24 lines!
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
		if (!flag && str[0] == '\'')
			flag = 1;
		else if (flag == 1 && str[0] == '\'')
			flag = 0;
		if (!flag && str[0] == '$' && str[1] != '$')
		{
			i += ft_strlcpy(&dest[i], src, ft_strlen(src) + 1);
			str = next_available_var(str);
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

	/*debug*/printf("str:%s. %zu+1\n", *cmd_line, ft_strlen(*cmd_line));
	i = ft_strlen(*cmd_line);
	/*debug*/printf("str:%lu, name:%lu, start:%lu\n malloc:%lu\n", ft_strlen(*cmd_line), ft_strlen(name), ft_strlen(src), i - ft_strlen(name) + ft_strlen(src));
	/*debug*/printf("check_replace_var:same! start:%s\n", src);	
	malloc_chr_ptr(&tmp, i - ft_strlen(name) + ft_strlen(src));
	copy_shell_var(*cmd_line, tmp, src);
	// /*debug*/printf("res:%s, %d\n", tmp, i);
	free(*cmd_line);
	*cmd_line = tmp;
}

// 24 lines!
/*
 * child function in shell_var_expansion, checks if $var entry exist in t_list
 * yes: remalloc *cmd_line & copy over the content + expansion
 * no : replace $var with ' ' spaces
 */
void	check_shell_var(t_list *vars, char *name, char **cmd_line, char *str)
{
	char	**tmp;
	int		flag;
	char	*start;

	flag = 0;
	/*debug*/printf("check_shell_var:ent:%s\n", *cmd_line);
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
	if (!flag) // if name !found, should start replacing from str
	{
		// /*debug*/printf("notfound! bf:%s.\n", *cmd_line);
		// start = ft_strchr(*cmd_line, '$');
		// start = *cmd_line;
		// while (start[0] && start[0] != '$')
		// {
		// 	if (start[0] && is_target("\'\"", start[0]))
		// 		start = skip_if_quote(start, start[0]);
		// 	else
		// 		start++;
		// 	/*debug*/printf("progress:%s\n", start);
		// }
		// if (!ft_isalpha(start[1]))
			// return ;
		start = str;
		*start++ = ' ';
		while (start && start[0] && !is_target(" $\'\"\t\n\v\f\r", start[0]))
			*start++ = ' ';
		/*debug*/printf("notfound! updated:%s.\n", *cmd_line);
	}
}
