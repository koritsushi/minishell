/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:34 by mliyuan           #+#    #+#             */
/*   Updated: 2025/02/15 23:07:49 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

/*
pwd
https://manual.cs50.io/3/getcwd
https://sites.uclouvain.be/SystInfo/manpages/man3/getcwd.3posix.html
https://stackoverflow.com/questions/9449241/where-is-path-max-defined-in-linux
https://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html
https://pubs.opengroup.org/onlinepubs/7908799/xsh/getcwd.html
*/
void    getpwd()
{
	char	buffer[PATH_MAX];
	char	*ret;

	ret = getcwd(buffer, PATH_MAX);
    if (ret == NULL)
	{
		printf("get working directory fail\n", 1);
		if (errno == ERANGE || errno == ENAMETOOLONG)
			printf("Path exceeds max buffer length, error code:%s\n", sterror(errno));
		else if (errno == ENOMEM)
			printf("could not allocate memory for path, error code:%s\n", sterror(errno));
	}
	ft_putstr_fd(buffer, 1);
}

//cd
void    chgwd()
{

}

//env 
void    env()
{
    
}


/*
    echo (option -n Only)
    this funtion takes in 2d array string
    so echo consider 1st parameter 
    and -n 2nd parameter, if str arg is NULL
    the while loop will continue 
    loop based on how many argument count
    ft_putstr_fd will do nothing if arg is NULL
*/
void    echo(int argc, char **args)
{
    int i;

    i = 1;
    if (argc == 1)
        return ft_putstr_fd("\n", 1);
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

//export 
void	export()
{

}

//unset
void	unset()
{
	
}