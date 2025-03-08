/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:54:11 by hsim              #+#    #+#             */
/*   Updated: 2025/03/08 11:48:24 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

char	*skip_if_quote(char *str, char symbol)
{
	char	*new;

	new = str;
	if (str[0] == symbol) // ' "
	{
		/*debug*/printf("skip \033[35m%c\033[0m =\033[90m%s\033[0m\n", symbol, new);
		new = ft_strchr(new + 1, symbol);
		printf("after_skip=\033[90m%s\033[0m.\n", new);
		if (new && new[1] && is_target(" \t\n\v\f\r", new[1]))
			new = skip_spaces(new + 1, " \t\n\v\f\r");
	}
	return (new);
}

/* checks str if has both < and > redirs */
int	has_mix_redirs(char *str)
{
	int	flag;

	flag = 0;
	if (str && str[0] && is_target(str, '<'))
		flag = 1;
	if (str && str[0] && is_target(str, '>'))
		return (flag == 1);
	return (0);
}

int	check_var_syntax(char *str)
{
	char	*new;

	/* mix in/out files */
	/* has other cmds */
	/* syntax incorrect: have spaces before/after '=' */
	/* '=' happen before ' " */
	new = str;

	/* mix in/out files */
	if (has_mix_redirs(str))
		return (0);
	/* truncate to var=1234*/
	while (new && new[0])
	{
		if (new[0] != '=' && new[1] && is_target("'\"", new[1]))
			return (ft_perror_fd("🚨 debug:Other cmd detected!\n", 2, 0));
			// new = skip_if_quote(new, new[0]);
		if (!new || !new[0])
			return (ft_perror_fd("\033[90mEnd of string!\033[0m\n", 2, 0));
		if (new[1] == '=' && \
			((new[0] && is_target(" \t\n\v\f\r<>|&", new[0])) || \
			(new[2] && is_target(" \t\n\v\f\r<>|&", new[2]))))
			return (ft_perror_fd("🚨 Syntax error! spaces before or after '='!\n", 2, 0));
		/* if new[1] == '=' */
		/* check if_errors , return */
		/* else if after '=' is ' or " , skip*/
		/* new++ & continue */
		else if (new[1] == '=' && (new[2] == '\'' || new[2] == '"'))
			new = skip_if_quote(new + 2, new[2]);
		new++;
	}
	return (1);
}

/*
 * child function in extract_vars,
 * searches in str for var_name & save til before '='
 * uses malloc
 */
void	get_var_name(char **dest, char *str)
{
	char	*new;
	int		len;

	len = 0;
	new = skip_spaces(str, " \t\n\v\f\r"); //optional
	while (new[len] && new[len] != '=')
		len++;
	/*debug*/printf("len=%d, leftover=%s\n", len, &new[len]);
	if (new && malloc_chr_ptr(dest, (len + 1)))
		ft_strlcpy(*dest, new, len + 1);
}

/*
 * trunc current variable to the beginning of next variable
 * if encounter ' ", skip; if encounter spaces, break
 */
char	*find_next_var(char *str)
{
	// char	*new;

	while (str && str[0])
	{
		if (str[0] == '\'' || str[0] == '"')
		{
			/*debug*/printf("\nbf_new=%s, str[0]=%c\n", str + 1, str[0]);
			str = skip_if_quote(str, str[0]);
			/*debug*/printf("new=%s\n\n", str);
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

int	count_malloc_vars(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			printf("count_malloc_vars: i=%d, %s.\n", i, &str[i]);
			printf("%d+1\n", (int)(ft_strchr(&str[i + 1], str[i]) - &str[i]));
			i += (int)(ft_strchr(&str[i + 1], str[i]) - &str[i]);
			return (i + 1 - 2);
		}
		else if (str[i] && is_target(" \t\n\v\f\r", str[i]))
			return (i);
		i++;
	}
	return (i);
}

/* copies src to dest, skips when encountered quote sign ' " */
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
		if (!flag && (src[0] == '\'' || src[0] == '"'))
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

	head = vars;
	while (head)
	{
		/*if found*/
		if (ft_strnstr(head->content, name, ft_strlen(head->content)))
		{
			/* trunc new up to first spaces skipping""*/
			/* frees old pointer */
			free(head->content);
			/*overwrite*/
			head->content = ft_strdup(new);
			*flag = 1;
			break ;
		}
		head = head->next;
	}
}

/* search for var name in linked list, replace data or add to list */
void	extract_vars(t_list **vars, char *str)
{
	int		flag;
	char	*tmp;
	char	*new;
	// t_list	*head;

	/* scan through string */
	/* search for name in linked list, if found, replace */
	while (str && str[0])
	{
		// head = *vars;
		flag = 0;
		str = skip_spaces(str, " \t\n\v\f\r");
		/* get_var_name */
		/*count & copy variable name*/
		get_var_name(&tmp, str);
		/*debug*/printf("var_name=%s\n", tmp);
		/*debug*/printf("var_len=%d\n", count_malloc_vars(str));
		malloc_chr_ptr(&new, count_malloc_vars(str) + 1);
		copy_vars(new, str, count_malloc_vars(str));

		/*search in all linked list*/
		check_replace_dup(*vars, tmp, new, &flag);
		if (!flag)
		{
			/*if !found && !flag*/
			/* trunc new up to first spaces skipping""*/
			/*debug*/printf("saved: new=\033[96m%s\033[0m.\n", new);
			ft_lstadd_back(vars, ft_lstnew(ft_strdup(new)));
		}
		/*free variable name*/
		free(new);
		free(tmp);
		/*skips new to the next var*/
		/*debug*/printf("before: str=%s\n", str);
		str = find_next_var(str);
		if (str && str[0])
		/*debug*/printf("find_next_var: str=\033[92m%s\033[0m.\n", str);
	}
}

/* child function to get_variables, saves variables in linked list */
void	process_vars(t_list **vars, char *str)
{
	char	*new;
	char	**tmp;
	char	**fin;

	/*split infile & outfile*/
	/* <infile var=123 > outfile */
	/* <infile > outfile var=123*/

	/* <infile var=123 */
	/* var=123 < infile */
	/* > outfile var=123 */
	/* var=123 > outfile*/

	/* if var var, save last var	*/
	/* if var1 var2, save both var	*/
	/* save var: skip ' " quotes	*/
	new = str;
	new = skip_spaces(new, "<> \t\n\v\f\r");
	new = skip_if_symbol(new, str[0], '<');
	new = skip_if_symbol(new, str[0], '>');
	/*debug*/printf("vars_before=%s\n", new);
	if (has_more_str(new, "<>"))
	{
		tmp = ft_split_shell(new, "<>");
		fin = ft_split_shell(tmp[0], " \t\n\v\f\r");
		new = ft_strdup(fin[0]);
		/*debug*/printf("fin[0]=%s|\n", fin[0]);
		free_chr_ptr((void **)tmp);
		free_chr_ptr((void **)fin);
	}
	else
	{
		extract_vars(vars, new);
		/* split by spaces */
		/* search for name in linked list, if found, replace */
		// new = ft_strdup(new);
	}
	// ft_lstadd_back(vars, ft_lstnew(new));
}

int	get_variable(t_list **vars, char *str)
{
	(void)	vars;
	char	*new;

	new = skip_spaces(str, " \t\n\v\f\r");
	if (new[0] && !is_target(new, '='))
		return (0);
	/* check_var_syntax */
	/* if ok, copy to vars & update str */
	if (check_var_syntax(new))
	{
		/* if no pipes, copy_vars */
		if (!is_target(new, '|')) //put a flag for multiple_cmd
			process_vars(vars, new); //only extract the last one
	}
	/* update_str '=' with ' '*/
	return (1);
}