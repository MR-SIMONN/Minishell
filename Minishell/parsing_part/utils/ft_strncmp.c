/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:10:31 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/12 15:10:33 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int    ft_strncmp(const char *s1, char *s2, size_t ncmp)
{
    size_t    i;

    i = 0;
    while (i < ncmp && s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
        {
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        }
        i++;
    }
    if (i < ncmp && (s1[i] || s2[i]))
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    return (0);
}