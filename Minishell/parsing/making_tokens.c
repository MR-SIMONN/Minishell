/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:34:46 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/26 17:48:46 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void     make_tokens(char **t, t_token **p, t_data *d)
{
    int i;

    i = 0;
	while (t[i])
	{
		ft_lstadd_back(p, ft_lstnew(t[i], d));
		i++;
	}
}

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
void    print_spaces_count(char *s, int f)
{
    int i = 0;
    int j = 0;
    while (s[i])
    {
        if (s[i] == ' ')
            j++;
        i++;
    }
    if (f == 0)
    {
        printf ("\nwe have ------->     [ %d ]      <------- input\n", j);
        printf ("\n%s\n\n", s);
    }
    else if (f == 1)
    {
        printf ("\nwe have ------->     [ %d ]      <------- mine\n", j);
        printf ("\n%s\n\n", s);        
    }
}

void    ft_lst_tokens(t_data *d)
{
    int len;
    char *str;
    char **tokens;

    len = extra_strlen(d->line);
    str = ft_strsdup(d->line, len, d);
    print_spaces_count(d->line, 0);
    print_spaces_count(str, 1);
    tokens = ft_split(str, ' ');
    make_tokens(tokens, &d->token, d);
}
