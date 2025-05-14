/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:27:47 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/14 15:27:08 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void    add_spaces(char *s, int *i, char *str, int *j)
{
    int f;

    f = 0;
    if (s[*i] && (is_one_symbol(s, *i) || is_two_symbols(s, *i)))
    {
        if (i > 0 && s[*i - 1] != ' ' && no_pipeout(s, *i))
            str[(*j)++] = ' ';
        if (is_two_symbols(s, *i))
        {
            str[(*j)++] = s[(*i)++];
            str[(*j)++] = s[(*i)++];
        }
        else
            str[(*j)++] = s[(*i)++];
        f = 1;
    }
    else
        str[(*j)++] = s[(*i)++];
    if (f)
    {
        if (s[*i] && s[*i] != ' ' && s[*i] != '>' && s[*i] != '<')
            str[(*j)++] = ' ';
        f = 0;
    }
}

void	handle_quotes(char *s, int *i, char *d, int *j)
{
	char	quote_type;

	quote_type = 0;
	if (s[*i] == '\'' || s[*i] == '\"')
	{
		quote_type = s[(*i)];
        d[(*j)++] = s[(*i)++];
		while (s[*i] && s[*i] != quote_type)
			d[(*j)++] = s[(*i)++];
		if (s[*i] == quote_type)
			d[(*j)++] = s[(*i)++];
	}
}

char *ft_strsdup(char *s1, int l, t_data *d)
{
    int     i;
    int     j;
    char    *s;

    i = 0;
    j = 0;
    s = ft_malloc (l + 1, d);
    while (s1[i])
    {
		handle_quotes(s1, &i, s, &j);
        if (!s1[i])
            break;
        add_spaces(s1, &i, s, &j);
    }
    s[j] = '\0';
	return (s);
}
