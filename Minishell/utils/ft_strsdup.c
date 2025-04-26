/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:27:47 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/26 18:56:34 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void    add_spaces(char *s, int *i, char *d, int *j, int f)
{
    if (is_one_symbol(s, *i) || is_two_symbols(s, *i))
    {
        if (i > 0 && s[*i - 1] != ' ')
            d[(*j)++] = ' ';
        if (is_two_symbols(s, *i))
        {
            d[(*j)++] = s[(*i)++];
            d[(*j)++] = s[(*i)++];
        }
        else
            d[(*j)++] = s[(*i)++];
        f = 1;
    }
    else
        d[(*j)++] = s[(*i)++];
    if (f)
    {
        if (s[*i] && s[*i] != ' ' && s[*i] != '>' && s[*i] != '<')
            d[(*j)++] = ' ';
        f = 0;
    }
}

char *ft_strsdup(char *s1, int l, t_data *d)
{
    int  i;
    int  j;
    int     f;
    char    *s;

    (1) && (i = 0, j = 0, f = 0, s = ft_malloc(l + 1, d));
    while (s1[i])
    {
        add_spaces(s1, &i, s, &j, f);
    }
	return (s[j] = '\0', s);
}
