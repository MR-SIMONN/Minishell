/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:33 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/23 18:10:35 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"
//input   --> echo -nnnnnnn hello
//output  --> "hello"

//intput  --> echo -nnnnnnnn -n -n -n hellofriend
//output  --> "hellofriend"

//input  --> echo -nnnnnnn -n -n -n -nnnn454 hekkiasa
//output --> "-nnnn454 hekkiasa"

int ft_check_option(char *s)
{
    int i;
    int flag;

    flag = 1;
    i = 0;
    if (s[i] == '-')
    {
        i++;
        if (s[i] == 'n')
        {
            while (s[i] == 'n')
            {
                flag = 0;
                i++;
            }
            if (s[i] != '\0')
                flag = 1;
        }
    }
    return (flag);
}

int echo_v(char **args)
{
    int i = 1;
    int newline = 1;
    if(!args[1])
    {
        ft_putstr_fd("\n", 1);
        return (0);
    }
    if (args[1] && ft_check_option(args[1]) == 0)
    {
        newline = 0;
        i = 2;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", 1);
    return (0);
}
