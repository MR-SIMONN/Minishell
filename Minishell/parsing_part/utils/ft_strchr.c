/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:49:56 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/12 14:49:58 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char *ft_strchr(const char *s, int c)
{
    if (!s)
        return (NULL);
    
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    
    if ((char)c == '\0')
        return ((char *)s);
    
    return (NULL);
}