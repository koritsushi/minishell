/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:34 by mliyuan           #+#    #+#             */
/*   Updated: 2025/02/14 16:26:37 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

//pwd
void    getcurrdp()
{
    
}

//cd
void    changepath()
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

int main (int arc, char **argv)
{
    echo(arc, argv);
    return (0);
}

//export 

//unset