/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:12:33 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/24 20:12:45 by ielouarr         ###   ########.fr       */
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