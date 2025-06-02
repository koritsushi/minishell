/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:35:57 by hsim              #+#    #+#             */
/*   Updated: 2025/05/29 18:42:07 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/expansion.h"

/*
 * child function in check_shell_var
 * mallocs new string, copy over from old string to new string
 * free & reassign *cmd_line to point to the new allocated string
 * src = content to copy over (eg var=content)
 * 1st ft_strlcpy: copy head
 * 2nd ft_strlcpy: copy content
 * 3rd ft_strlcpy: copy tail
 */
static void	check_replace_var(char **cmd_line, char *name, char *src, \
int len_head)
{
	int		i;
	char	*new;

	i = ft_strlen(*cmd_line) - ft_strlen(name) + ft_strlen(src);
	malloc_chr_ptr(&new, i);
	i = len_head + ft_strlen(name) + 1;
	ft_strlcpy(new, (*cmd_line), len_head + 1);
	len_head += ft_strlcpy(&new[len_head], src, ft_strlen(src) + 1);
	ft_strlcpy(&new[len_head], &(*cmd_line)[i], ft_strlen(&(*cmd_line)[i]) + 1);
	free(*cmd_line);
	*cmd_line = new;
}

/*
 * child function in check_shell_var,
 * clean up $var when it does not exist
 * copies leftover and remalloc cmd_line to point to new string
 * index = str - *cmd_line
 * uses malloc
 */
static void	copy_remove_var(char **cmd_line, int index, int name_len)
{
	int		tail;
	char	*dest;

	malloc_chr_ptr(&dest, ft_strlen(*cmd_line) - name_len);
	ft_strlcpy(dest, (*cmd_line), index + 1);
	tail = ft_strlen(&(*cmd_line)[index + name_len + 1]) + 1;
	ft_strlcpy(&dest[index], &(*cmd_line)[index + name_len + 1], tail);
	free(*cmd_line);
	*cmd_line = dest;
}

/*
 * child function in expand_shell_var, checks if $var entry exist in t_env
 * yes: remalloc *cmd_line & copy over the content + expansion
 * no : replace $var with ' ' spaces
 * return len of the expanded content
 */
static int	check_shell_var(t_env *vars, char *name, char **cmd_line, char *str)
{
	int		len;
	int		flag_exist;

	len = 0;
	flag_exist = 0;
	while (vars && !flag_exist)
	{
		if (ft_strlen(vars->env) == ft_strlen(name) && \
ft_strncmp(vars->env, name, ft_strlen(name)) == 0)
		{
			flag_exist = 1;
			len = ft_strlen(vars->content);
			check_replace_var(cmd_line, name, vars->content, str - (*cmd_line));
		}
		vars = vars->next;
	}
	if (!flag_exist)
		copy_remove_var(cmd_line, str - (*cmd_line), ft_strlen(name));
	return (len);
}

/*
 * child function in expand_shell_var
 * truncates name up to 1st occurence of non-alphabet or non-numbers
 */
static void	truncate_name_at_symbol(char *str)
{
	while (str && str[0])
	{
		if (!ft_isalnum(str[0]) && !is_target("_\'\"", str[0]))
		{
			str[0] = '\0';
			break ;
		}
		str++;
	}
}

/*
 * child function in shell_var_expansion
 * checks if $var entry exists, copy from *cmd_line to new string
 * remallocs cmd_line to point to new expanded string,
 * updates index number to point where expansion part done
 * index = str[index] position when entering this function
 * uses malloc
 */
char	*expand_shell_var(t_env *vars, char **cmd_line, char *str, int *index)
{
	char	**tmp;
	char	**fin;

	tmp = ft_split_shell(str, "$");
	fin = ft_split_shell(tmp[0], " \'\"\t\n\v\f\r");
	truncate_name_at_symbol(fin[0]);
	(*index) += check_shell_var(vars, fin[0], cmd_line, str);
	free_multiple_ptr(tmp, fin, NULL);
	return (*cmd_line);
}
