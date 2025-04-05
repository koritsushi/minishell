/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:35:57 by hsim              #+#    #+#             */
/*   Updated: 2025/04/05 19:18:48 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

/*
 * child function in check_shell_var
 * mallocs new string, copy over from old string to new string
 * free & reassign *cmd_line to point to the new allocated string
 * src = content to copy over (eg var=content)
 */
static void	check_replace_var(char **cmd_line, char *name, char *src)
{
	int		i;
	char	*new;

	/*debug*/printf("str:%s. %zu+1\n", *cmd_line, ft_strlen(*cmd_line));
	i = ft_strlen(*cmd_line);
	/*debug*/printf("str:%lu, name:%lu, content:%lu\n malloc:%lu\n", ft_strlen(*cmd_line), ft_strlen(name), ft_strlen(src), i - ft_strlen(name) + ft_strlen(src));
	/*debug*/printf("check_replace_var:same! start:%s\n", src);	
	malloc_chr_ptr(&new, i - ft_strlen(name) + ft_strlen(src));
	copy_shell_var(*cmd_line, new, src, ft_strlen(name) + 1);
	// /*debug*/printf("res:%s, %d\n", new, i);
	free(*cmd_line);
	*cmd_line = new;
}

// 24 lines!
/*
 * child function in expand_shell_var, checks if $var entry exist in t_env
 * yes: remalloc *cmd_line & copy over the content + expansion
 * no : replace $var with ' ' spaces
 */
static void	check_shell_var(t_env *vars, char *name, char **cmd_line, char *str)
{
	char	**tmp;
	int		flag_name;
	char	*content;

	flag_name = 0;
	/*debug*/printf("\033[93mcheck_shell_var:ent:\033[0m%s\n", *cmd_line);
	while (vars && !flag_name)
	{
		tmp = ft_split_shell(vars->content, "=");
		/*debug*/printf("check_replace_dup name:%s, %s\n", tmp[0], name);
		if (ft_strlen(tmp[0]) == ft_strlen(name) && \
			ft_strncmp(vars->content, name, ft_strlen(name)) == 0)
		{
			content = ft_strchr(vars->content, '=') + 1;
			check_replace_var(cmd_line, name, content);
			flag_name = 1;
		}
		free_chr_ptr((void **)tmp);
		vars = vars->next;
	}
	if (!flag_name)
	{
		// /*debug*/printf("notfound! bf:%s.\n", *cmd_line);
		content = str;
		*content++ = ' ';
		while (content && content[0] && !is_target(" $\'\"\t\n\v\f\r", content[0]))
			*content++ = ' ';
		/*debug*/printf("notfound! updated:%s.\n", *cmd_line);
	}
}

static void	truncate_name_at_symbol(char *str)
{
	while (str && str[0])
	{
		if (!ft_isalnum(str[0]) && !is_target("\'\"", str[0]))
		{
			str[0] = '\0';
			break ;
		}
		str++;
	}
}

/*
 * child function in shell_var_expansion
 * checks if $var entry exists, copy from *cmd_line
 * remallocs the new expanded string & return
 * uses malloc
 */
char	*expand_shell_var(t_env *vars, char **cmd_line, char *str)
{
	char	**tmp;
	char	**fin;

	tmp = ft_split_shell(str, "$");
	// /*debug*/printf("-----\nsplit:fin:\n");
	fin = ft_split_shell(tmp[0], " \'\"\t\n\v\f\r");
	truncate_name_at_symbol(fin[0]);
	// /*debug*/debug_print(tmp);
	/*debug*/printf(".....\nfin:\n");
	/*debug*/debug_print(fin);
	/*debug*/printf("-----\n");
	/*debug*/printf("expand_shell_var:var_name:%s, str:%s\n", fin[0], str);
	check_shell_var(vars, fin[0], cmd_line, str);
	free_multiple_ptr(2, tmp, fin);
	return (*cmd_line);
	// str = *cmd_line;
}