/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:34 by mliyuan           #+#    #+#             */
/*   Updated: 2025/04/25 16:37:03 by mliyuan          ###   ########.fr       */
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

//print current working directory
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
	t_env	*opwd;
	t_env	*cpwd;

	curr_dir = getpwd();
	if (curr_dir == NULL)
		return (-1);
	if (chdir(dir) == -1)
		return (printf("Minishell: cd : %s: %s\n", dir, strerror(errno)));
	else
	{
		cpwd = ft_lstnew_env("PWD", dir, 1);
		opwd = ft_lstnew_env("OLDPWD", curr_dir, 1);
		export(lst, cpwd);
		export(lst, opwd);
		ft_lstdelone_env(cpwd, free);
		ft_lstdelone_env(opwd, free);
	}
	return (0);
}

/*	echo (option -n Only)
    this funtion takes in 2d array string
    so echo consider 1st parameter 
    and -n 2nd parameter, if str arg is NULL
    the while loop will continue 
    loop based on how many argument count
    ft_putstr_fd will do nothing if arg is NULL
*/
int	ft_echo(int argc, char **args)
{
	int	nl;
	int	i;

	nl = 0;
	if (argc == 2 || args == NULL)
		return (printf("\n"));
	if (ft_strncmp(args[1], "-n", 2) == 0)
		nl = 1;
	i = 1 + nl;
	while (args[i] != NULL && i + nl < argc)
	{
		ft_putstr_fd(args[i++], 1);
		if (args[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (nl == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}

/*debugging and testing purposes
int	main(int argc, char **argv, char **env)
{
	t_ms	data;

	data.env_var = NULL;
	msh_init(&data, env);
	if (argc > 1)
	{
		if (strcmp(argv[1], "echo") == 0)
		{
			ft_echo(argc, argv+1);
		}
		else if (strcmp(argv[1], "pwd") == 0)
		{
			ft_pwd();
		}	
		else if (strcmp(argv[1], "cd") == 0)
		{
			ft_pwd();
			ft_cd(&data.env_var, argv[2]);
			ft_pwd();
		}
		env_print(&data.env_var);
		export_print(&data.env_var);
	}
	return (0);
}
*/
