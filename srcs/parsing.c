/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:54:11 by hsim              #+#    #+#             */
/*   Updated: 2025/03/11 14:36:09 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

/* if str[0] == quote, will skip it and return */
char	*skip_if_quote(char *str, char symbol)
{
	char	*new;

	new = str;
	if (str[0] == symbol) // ' "
	{
		// /*debug*/printf("skip \033[35m%c\033[0m =\033[90m%s\033[0m\n", symbol, new);
		new = ft_strchr(new + 1, symbol);
		// /*debug*/printf("after_skip_quote=\033[90m%s\033[0m.\n", new);
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
		{
			if (is_target(str, '|'))
				return (1);
			return (ft_perror_fd("🚨 debug:Other cmd detected!\n", 2, 0));
		}
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
		else if (new[1] == '=' && (new[2] == '\'' || new[2] == '\"'))
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

	/*debug*/printf("------\nget_var_name:\n");
	len = 0;
	new = skip_spaces(str, " \t\n\v\f\r"); //optional
	while (new[len] && new[len] != '=')
		len++;
	// /*debug*/printf("len=%d, leftover=%s\n", len, &new[len]);
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
			// printf("count_malloc_vars: i=%d, %s.\n", i, &str[i]);
			// printf("%d+1\n", (int)(ft_strchr(&str[i + 1], str[i]) - &str[i]));
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
	char	**tmp;
	size_t	len;

	head = vars;
	while (head && !*flag)
	{
		tmp = ft_split_shell(head->content, "=");
		/*debug*/printf("check_replace_dup name:%s, %s\n", tmp[0], name);
		/*if found*/
		len = ft_strlen(name);
		if (ft_strlen(tmp[0]) > len)
			len = ft_strlen(tmp[0]);
		if (ft_strncmp(head->content, name, len) == 0)
		{
			/*debug*/printf("check_replace_dup:found! name:%s\n", (char *)head->content);
			free(head->content);
			/*overwrite*/
			head->content = ft_strdup(new);
			*flag = 1;
		}
		free_chr_ptr((void **)tmp);
		head = head->next;
	}
}

// 18 lines!
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
		get_var_name(&name, str);
		/*debug*/printf("var_name=%s, var_len=%d\n", name, count_malloc_vars(str));
		/*count & copy variable name*/
		malloc_chr_ptr(&new, count_malloc_vars(str) + 1);
		copy_vars(new, str, count_malloc_vars(str));
		/*debug*/printf("copy_vars:%s\n", new);
		/*debug*/printf("---------\ncheck_replace_dup:\n");
		/*search in all linked list*/
		check_replace_dup(*vars, name, new, &flag);
		/*debug*/printf("---------\n");
		if (flag == 0)
		{
			/*if !found && !flag*/
			/* trunc new up to first spaces skipping""*/
			/*debug*/printf("saved: new=\033[96m%s\033[0m.\n", new);
			ft_lstadd_back(vars, ft_lstnew(ft_strdup(new)));
		}
		/*free variable name*/
		free(new);
		free(name);
		/*skips new to the next var*/
		/*debug*/printf("before: str=%s\n", str);
		str = find_next_var(str);
		if (str && str[0])
		/*debug*/printf("find_next_var: str=\033[92m%s\033[0m.\n", str);
	}
}

/*
 * child function in process_vars,
 * skips all < infile & > outfile redirections, updates *new */
static void	skip_redirs(char *str, char **new)
{
	while (str[0] == '<' || str[0] == '>')
	{
		*new = str;
		*new = skip_spaces(*new, "<> \t\n\v\f\r");
		/*debug*/printf("skip_spaces=%s\n", *new);
		*new = skip_if_symbol(*new, str[0], '<');
		/*debug*/printf("skip_< =%s\n", *new);
		*new = skip_if_symbol(*new, str[0], '>');
		/*debug*/printf("skip_> =%s\n", *new);
		str = skip_spaces(str, "<> \t\n\v\f\r");
		while (str[0] && !is_target(" \t\n\v\f\r", str[0]))
			str++;
		str = skip_spaces(str, " \t\n\v\f\r");
		/*debug*/printf("str =%s\n", str);
	}
}

// 19 lines!
/* child function in get_variables, saves variables in linked list */
void	process_vars(t_list **vars, char *str)
{
	char	*new;
	char	**tmp;
	char	**fin;
	int		x;

	/*split infile & outfile*/
	/* <infile var=123 > outfile */
	/* <infile > outfile var=123*/

	/* <infile var=123 */
	/* var=123 < infile */
	/* > outfile var=123 */
	/* var=123 > outfile*/
	/* var=123 var2=456 > outfile >out2 */

	/* if var var, save last var	*/
	/* if var1 var2, save both var	*/
	/* save var: skip ' " quotes	*/
	new = str;
	skip_redirs(str, &new);
	/*debug*/printf("vars_before=%s.\n", new);
	/* if at beginning < > */
	if (has_more_str(new, "<>"))
	{
		x = 0;
		tmp = ft_split_shell(new, "<>");
		fin = ft_split_shell(tmp[0], " \t\n\v\f\r");

		/*debug*/printf("--------\ntmp:\n");
		/*debug*/debug_print(tmp);
		/*debug*/printf("--------\nfin:\n");
		/*debug*/debug_print(fin);
	
		while (fin && fin[x])
			extract_vars(vars, fin[x++]);

		// /*debug*/printf("tmp[0]:%s.\n", tmp[0]);
		// extract_vars(vars, tmp[0]);
		free_chr_ptr((void **)tmp);
		free_chr_ptr((void **)fin);
	}
	else
		extract_vars(vars, new);
}

/*
 * child function in replace_var_space, 
 * if is empty spaces after last pipe '|', replace last pipe with spaces ' '
 */
static void	replace_last_pipe(char *str)
{
	char	*new;

	if (ft_strrchr(str, '|'))
	{
		new = ft_strrchr(str, '|');
		/*debug*/printf("end_:\033[90m%s\033[0m.\n", new);
		while (new[1] && is_target(" \t\n\v\f\r", new[1]))
			new++;
		if (new[1] == '\0')
		{
			new = ft_strrchr(str, '|');
			new[0] = ' ';
		}
	}
}

/*
 * child function in replace_var_space,
 * writes entire quoted area to spaces ' ' if quote symbol ' " detected
 */
void	replace_quote_space(char **str)
{
	char	*new;
	int		i;

	new = *str;
	i = 0;
	if (new[0] && is_target("'\"", new[0]))
	{
		i = (int)(ft_strchr(&new[1], new[0]) - &new[0]);
		while (i >= 0)
			new[i--] = ' ';
		/*debug*/printf("i=%d, %s\n", i, new);
	}
}

// 25 lines!!
/* overwrites var assignment in str (eg var=123) to blank space ' ' */
void	replace_var_space(char *str)
{
	char	*new;

	/* searches location of '=' */
	/* reverse search the space before '=' */
	/* fill all with ' ' until isalnum || !| && spaces*/

	new = str;
	while (new && new[0])
	{
		if (new[0] == '\'' || new[0] == '"')
			new = skip_if_quote(new, new[0]) - 1;
		else if (new && new[0] == '=')
		{
			while (new[0 - 1] && !is_target(" \t\n\v\f\r", new[0 - 1]))
				new--;
			while (new[0] && !is_target("<>|", new[0]))
			{
				if (is_target("\'\"", new[0]))
					replace_quote_space(&new);
				else if (!is_target(" \t\n\v\f\r", new[0]))
					new[0] = ' ';
				new++;
			}
			if (new[0] == '|')
				new[0] = ' ';
		}
			// /*debug*/printf("replace_var_sp:\033[90m%s\033[0m.\n", new);
		new++;
	}
	replace_last_pipe(str);
}

/*
 * checks if variable syntax is correct,
 * overwrite & save if variable has existed
 */
int	get_variable(t_list **vars, char *str)
{
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
		/* update_str '=' with ' '*/
		replace_var_space(str);
	}
	return (1);
}
