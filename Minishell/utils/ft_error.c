/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:10:42 by ielouarr          #+#    #+#             */
/*   Updated: 2025/04/20 16:49:50 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void ft_error(char *message)
{
    int i;
    
    i = 0;
    while(message[i])
        write(2, &message[i], 1);
    exit(EXIT_FAILURE);
}