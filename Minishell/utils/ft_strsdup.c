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

char	*ft_strsdup(char *s1, int l, t_data *d)
{
	size_t	i;
    size_t  j;
    int     f;
	char	*s;

    (1) && (i = 0, j = 0, f = 0, s = ft_malloc (l + 1, d));
	s = ft_malloc (l + 1, d);
	while (s1[i])
	{
        if (is_one_symbol(s1, i) || is_two_symbols(s1, i))
        {
            if (s1[i - 1] && s1[i - 1] != ' ')
                s[j++] = ' ';
            f = 1;
        }
		s[j++] = s1[i++];
		if (f)
		{
		    if (s1[i] != ' ' && s1[i] != '>' && s1[i] != '<')
		    {
		        s[j++] = ' ';
                f = 0;
		    }
		}
	}
	return (s[j] = '\0', s);
}