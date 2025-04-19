/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:10:42 by ielouarr          #+#    #+#             */
/*   Updated: 2025/04/20 00:24:18 by moel-hai         ###   ########.fr       */
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