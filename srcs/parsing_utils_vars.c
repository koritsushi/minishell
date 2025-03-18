/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:12:43 by hsim              #+#    #+#             */
/*   Updated: 2025/03/18 12:12:35 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

/*
 * child function in get_var_name,
 * checks if var_name is same as assigned content (eg var=$var)
 */
static int  is_self_assigned(char *str, char *name)
{
	int		flag;
	size_t	len;
	char	*check;

	flag = 0;
	len = 0;
	while (str[len + 1] && !is_target(" \t\n\v\f\r", str[len + 1]))
		len++;
	if (malloc_chr_ptr(&check, (len + 1)))
		ft_strlcpy(check, str + 1, len + 1);
	/*debug*/printf("compare:%s\n", check);
	len = ft_strlen(name);
	if (ft_strlen(check) > len)
		len = ft_strlen(check);
	if (ft_strncmp(name, check, len) == 0)
		flag = 1;
	free(check);
	return (flag);
}

/*
 * child function in extract_vars,
 * searches in str for var_name & save til before '='
 * if var is self assigned (var=$var), frees & return
 * uses malloc
 */
int get_var_name(char **dest, char *str)
{
	char	*new;
	int		len;

	// /*debug*/printf("------\nget_var_name:\n");
	len = 0;
	new = skip_spaces(str, " \t\n\v\f\r"); //optional
	while (new[len] && new[len] != '=')
		len++;
	// /*debug*/printf("len=%d, leftover=%s\n", len, &new[len]);
	if (new && malloc_chr_ptr(dest, (len + 1)))
		ft_strlcpy(*dest, new, len + 1);
	new += len + 1;
	/*debug*/printf("get_var_name:af:%s.\n", new);
	if (new[0] == '$' && new[1] && is_self_assigned(new, *dest))
	{
		free(*dest);
		return (0);
	}
	return (1);
}

/*
 * child function in extract_vars
 * trunc current variable to the beginning of next variable
 * if encounter ' ", skip; if encounter spaces, break
 */
char	*find_next_var(char *str)
{
	while (str && str[0])
	{
		if (str[0] == '\'' || str[0] == '"')
		{
			// /*debug*/printf("\nbf_new=%s, str[0]=%c\n", str + 1, str[0]);
			str = skip_if_quote(str, str[0], 1);
			// /*debug*/printf("new=%s\n\n", str);
			if (str[0] == '\'' || str[0] == '"')
				return (str + 1);
			return (str);
		}
		else if (str[0] && is_target(" \t\n\v\f\r", str[0]))
			return (skip_spaces(str, " \t\n\v\f\r"));
		str++;
	}
	return (NULL);
}

/*
 * child function in extract_vars,
 * counts appropriate size to malloc string
 */
int	count_malloc_vars(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			// printf("count_malloc_vars: i=%d, %s.\n", i, &str[i]);
			// printf("%d+1\n", (int)(ft_strchr(&str[i + 1], str[i]) - &str[i]));
			i += (int)(ft_strchr(&str[i + 1], str[i]) - &str[i]);
			if (str[i] == '\"')
				return (i + 1 - 2);
			return (i + 1);
		}
		else if (str[i] && is_target(" \t\n\v\f\r", str[i]))
			return (i);
		i++;
	}
	return (i);
}

/*
 * child function in extract_vars,
 * copies src to dest, skips when encountered double quote sign "
 */
void	copy_vars(char *dest, char *src, int len)
{
	int		x;
	int		flag;
	char	symbol;

	if (!dest || !src)
		return ;
	x = 0;
	flag = 0;
	symbol = '\0';
	while (src[0] && x < len)
	{
		// if (!flag && (src[0] == '\'' || src[0] == '\"'))
		if (!flag && src[0] == '\"')
		{
			symbol = src[0];
			flag = 1;
		}
		if (src[0] != symbol)
			dest[x++] = src[0];
		src++;
	}
	dest[x] = '\0';
}

/*
 * child function in extract_vars,
 * search for var name in linked list, & replace data if dup found
 */
void	check_replace_dup(t_list *vars, char *name, char *new, int *flag)
{
	t_list	*head;
	char	**tmp;
	size_t	len;

	head = vars;
	while (head && !*flag)
	{
		tmp = ft_split_shell(head->content, "=");
		// /*debug*/printf("check_replace_dup name:%s, %s\n", tmp[0], name);
		/*if found*/
		len = ft_strlen(name);
		if (ft_strlen(tmp[0]) > len)
			len = ft_strlen(tmp[0]);
		if (ft_strncmp(head->content, name, len) == 0)
		{
			// /*debug*/printf("check_replace_dup:found! name:%s\n", (char *)head->content);
			free(head->content);
			/*overwrite*/
			head->content = ft_strdup(new);
			*flag = 1;
		}
		free_chr_ptr((void **)tmp);
		head = head->next;
	}
}

// 19 lines!
/*
 * child function in process_vars,
 * searches & replace duplicate var name in linked list, 
 * or add new var entry to list
 */
void	extract_vars(t_list **vars, char *str)
{
	int		flag;
	char	*name;
	char	*new;

	/* scan through string */
	/* search for name in linked list, if found, replace */
	while (str && str[0])
	{
		flag = 0;
		str = skip_spaces(str, " \t\n\v\f\r");
		/* get_var_name */
		if (!get_var_name(&name, str))
			return ;
		/* if assignment content = $var_name, break */
		/*count & copy variable name*/
		/*debug*/printf("var_name=%s, var_len=%d+1\n", name, count_malloc_vars(str));
		malloc_chr_ptr(&new, count_malloc_vars(str) + 1);
		copy_vars(new, str, count_malloc_vars(str));
		// /*debug*/printf("copy_vars:%s\n", new);
		// /*debug*/printf("---------\ncheck_replace_dup:\n");
		check_replace_dup(*vars, name, new, &flag);
		// /*debug*/printf("---------\n");
		if (flag == 0)
		{
			/*if !found && !flag*/
			// /*debug*/printf("saved: new=\033[96m%s\033[0m.\n", new);
			ft_lstadd_back(vars, ft_lstnew(ft_strdup(new)));
		}
		/*free variable name*/
		free(new);
		free(name);
		/*skips new to the next var*/
		str = find_next_var(str);
		// if (str && str[0])
		// /*debug*/printf("find_next_var: str=\033[92m%s\033[0m.\n", str);
	}
}
