/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:34:46 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/24 21:33:07 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int extra_strlen(char *s)
{
    int i = 0;
    int len = 0;

    while (s[i])
    {
        if (is_two_symbols(s, i))
        {
            handle_symbols(s, &len, i);
            len += 2;
            i++;
        }
        else if (is_one_symbol(s, i))
        {
            if ((i > 0 && s[i - 1] != ' '))
                len++;
            if (s[i + 1] && s[i + 1] != ' ')
                len++;
            len++;
        }
        else
            len++;
        i++;
    }
    return len;
}

char    *make_thestring(t_data *d)
{
    int len;
    char *str;

    len = extra_strlen(d->line);
    str = ft_strsdup(d->line, len, d);
    // do whatchu gotta do here
    return (str);
}