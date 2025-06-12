/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:43 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/23 18:06:07 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void exit_v(char **args)
{
    long status;
    int is_out_range;
    
    is_out_range= 0;
    status = 0;
    if(!args[1])
    {
        ft_putstr_fd("exit", 1);
        exit(0);
    }
    if (args[1])
    {
        status = ft_atol(args[1], &is_out_range);
        if (!is_digit(args[1]) || is_out_range)
            ft_putstr_fd("exit : numeric argument required\n", 2);
    }
    if(args[2])
            ft_putstr_fd("exit : too many arguments", 2);
    if (is_digit(args[1]))
        ft_putstr_fd("exit", 1);
        exit((unsigned char)status);
}
