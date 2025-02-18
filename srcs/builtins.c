/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:34 by mliyuan           #+#    #+#             */
/*   Updated: 2025/02/18 22:41:13 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

/*	pwd
	first parameter require a buffer with define size
	second parameter require a size_t/int/long size 
	same as define size in buffer variable
	PATH_MAX is define as 4096 in builins.h
	PATH_MAX is not used from header <limits.h> as 
	it has variant define size in different operating system
	
	Reference
	https://manual.cs50.io/3/getcwd
	https://sites.uclouvain.be/SystInfo/manpages/man3/getcwd.3posix.html
	https://stackoverflow.com/questions/9449241/where-is-path-max-defined-in-linux
	https://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html
	https://pubs.opengroup.org/onlinepubs/7908799/xsh/getcwd.html
*/
char	*getpwd(void)
{
	char	buffer[PATH_MAX];
	char	*ret;

	ret = getcwd(buffer, PATH_MAX);
	if (ret == NULL)
	{
		free(ret);
		printf("-minishell: pwd: get working directory fail!, error:%s\n", strerror(errno));
		return (NULL);
	}
	return (ret);
}

void	printpath(void)
{
	ft_putstr_fd(getpwd(), 1);
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
	char	*cdir;

	cdir = getpwd();
	if (strncmp(cdir, dir, ft_strlen(cdir)))
	{
		free(cdir);
		return ;
	}
	free(cdir);
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

// int main (int arc, char **argv)
// {
//     echo(arc, argv);
//     return (0);
// }