/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:34 by mliyuan           #+#    #+#             */
/*   Updated: 2025/06/02 15:58:29 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

/*	pwd
first parameter require a buffer with define size
second parameter require a size_t/int/long size 
same as define size in buffer variable
PATHMX is define as 4096 in builins.h
PATHMX is to similate PATH_MAX from header <limits.h>
PATH_MAX was not used due to variable define size in 
different operating system

Reference
https://manual.cs50.io/3/getcwd
https://sites.uclouvain.be/SystInfo/manpages/man3/getcwd.3posix.html
https://stackoverflow.com/questions/9449241/where-is-path-max-defined-in-linux
https://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html
https://man7.org/linux/man-pages/man3/getcwd.3.html
*/
char	*getpwd(void)
{
	char	*buffer;
	char	*ret;

	buffer = NULL;
	ret = getcwd(buffer, PATHMX);
	if (ret == NULL)
	{
		printf("-minishell: pwd: %s\n", strerror(errno));
		return (NULL);
	}
	return (ret);
}

/* print current working directory */
int	ft_pwd(void)
{
	char	*pwd;

	pwd = getpwd();
	if (pwd == NULL)
		return (-1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

/*
 * child function in ft_cd
 * updates env_path to new chdir path if chdir() success
 */
static void	update_env_path(t_env *lst, char *str, char *curr_dir)
{
	char	*new;

	new = expand_relative_path(str, curr_dir);
	ft_lst_replace_if(lst, "PWD", new);
	ft_lst_replace_if(lst, "OLDPWD", curr_dir);
	if (ft_strncmp("../", str, 3) == 0 || ft_strncmp("..", str, 2) == 0)
		free(new);
}

/*	
	change directory
	will update env OLDPWD and PWD var when changing directory
	not yet handle ~ or might need expansion
	no arguments = cd behaviour will change directory to root
	directory
	
	error exception 
	if user try to change into same directory
	should have no changes and straight return
	if user tries to input signal from keyboard
	such as CTRL-V where c Program read as NULL, 
	it will return error

	returms -1 on error and 0 on success
*/
int	ft_cd(t_env **lst, char *dir)
{
	char	*curr_dir;
	char	**tmp;
	int		exit_code;
	char	*error;

	if (!dir)
		return (0);
	exit_code = 0;
	tmp = ft_split_shell(dir, " \t\n\v\f\r");
	curr_dir = getpwd();
	if (curr_dir == NULL)
		return (-1);
	if (chdir(tmp[0]) != 0)
	{
		error = ft_strjoin("-minishell: cd: ", tmp[0]);
		perror(error);
		free(error);
		exit_code = 1;
	}
	else
		update_env_path(*lst, tmp[0], curr_dir);
	free_chr_ptr((void **)tmp);
	free(curr_dir);
	return (exit_code);
}

/*	echo (option -n Only)
    this funtion takes in 2d array string
    so echo consider 1st parameter 
    and -n 2nd parameter, if str arg is NULL
    the while loop will continue 
    loop based on how many argument count
    ft_putstr_fd will do nothing if arg is NULL
*/
int	ft_echo(char **args)
{
	int	i;
	int	nl;

	nl = 0;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
		nl = 1;
	i = 1 + nl;
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i++], 1);
		if (args[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (nl == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
