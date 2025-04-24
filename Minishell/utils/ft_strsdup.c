/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:27:47 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/24 22:16:54 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*ft_strsdup(char *s1, int len, t_data *d)
{
	size_t	i;
    size_t  j;
	char	*str;

	i = 0;
    j = 0;
	str = ft_malloc (len + 1, d);
	while (s1[i])
	{
        if (is_one_symbol(s1, i))
        {
            if (s1[i - 1] && s1[i - 1] != ' ')
                str[j++] = ' ';
        }
		str[j] = s1[i];
		i++;
        j++;
	}
	str[i] = '\0';
	return (str);
}
