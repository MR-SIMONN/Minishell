/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:43 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/19 21:23:08 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void exit_v(char **args)
{
    long status;
    int is_out_range;
    
    is_out_range= 0;
    status = 0;

    ft_putstr_fd("exit\n", 1);
    if(!args[1])
        exit(0);
    if (!is_digit(args[1]) || (status = ft_atol(args[1], &is_out_range), is_out_range))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        exit(255);
    }
    if(args[2])
    {
        ft_putstr_fd("exit : too many arguments", 2);
        return;
    }
        
    exit((unsigned char)status);
}
