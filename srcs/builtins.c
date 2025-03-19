/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:34 by mliyuan           #+#    #+#             */
/*   Updated: 2025/03/18 15:24:40 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

/*	pwd
	first parameter require a buffer with define size
	second parameter require a size_t/int/long size 
	same as define size in buffer variable
	PATHMX is define as 4096 in builins.h
	PATHMX is to similate PATH_MAX from header <limits.h>
	PATH_MAX was not used due to variable define size in different operating system
	Reference
	https://manual.cs50.io/3/getcwd
	https://sites.uclouvain.be/SystInfo/manpages/man3/getcwd.3posix.html
	https://stackoverflow.com/questions/9449241/where-is-path-max-defined-in-linux
	https://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html
	https://pubs.opengroup.org/onlinepubs/7908799/xsh/getcwd.html
*/
char	*getpwd(void)
{
	char	buffer[PATHMX];
	char	*ret;

	ret = getcwd(buffer, PATHMX);
	if (ret == NULL)
	{
		printf("-minishell: pwd: get working directory fail!, error:%s\n", strerror(errno));
		return (NULL);
	}
	return (ret);
}

void	printpath(void)
{
	ft_putstr_fd(getpwd(), 1);
	ft_putstr_fd("\n", 1);
}

/*	cd
	change directory
	error exception 
	if user try to change into same directory
	should have no changes and straight return
	if user tries to input signal from keyboard
	such as CTRL-V, it will return error
*/
void	chgwd(char *dir)
{
	char *curr_dir;

	curr_dir = getpwd();
	if (curr_dir == NULL)
		return ;
	if (strncmp(curr_dir, dir, ft_strlen(dir)) == 0)
		return ;
	if (chdir(dir) == -1)
		printf("cd : %s: No such file or directory, error:%s", dir, strerror(errno));
}

/*	echo (option -n Only)
    this funtion takes in 2d array string
    so echo consider 1st parameter 
    and -n 2nd parameter, if str arg is NULL
    the while loop will continue 
    loop based on how many argument count
    ft_putstr_fd will do nothing if arg is NULL
*/
void	echo(int argc, char **args)
{
	int	i;

	i = 1;
	if (argc == 1)
		return (ft_putstr_fd("\n", 1));
	while (i < argc)
	{
		if (strncmp(args[1], "-n", 2) == 0)
			i++;
		ft_putstr_fd(args[i++], 1);
		ft_putstr_fd(" ", 1);
	}
	if (strncmp(args[1], "-n", 2) != 0)
		ft_putstr_fd("\n", 1);
}

/*
int	main(int argc, char **argv)
{
	chgwd(argv[1]);
	return (argc);
}
*/
