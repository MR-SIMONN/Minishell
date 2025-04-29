/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:14:07 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/29 22:52:35 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void    syntax_error (char *s, t_data *d)
{
    printf ("%s\n", s);
    clear_trash(&d->heap);
    exit (1);
}

int is_symbol(char c)
{
    return(c == '>' || c == '<' || c == '|');
}

void    check_one(char *s, int i, t_data *d)
{
    if (s[i] == '>' && s[i])
    {
        i++;
        if (is_symbol(s[i]) && s[i] != '|' && s[i])
            syntax_error("syntax error", d);
    }
    if (s[i] == '<' && s[i])
    {
        i++;
        if (is_symbol(s[i]) && s[i] != '>' &&s[i])
            syntax_error("syntax error", d);
    }
}

void    check_two(char *s, int i, t_data *d)
{
    if (s[i] == '>' && s[i])
    {
        i += 2;
        if (is_symbol(s[i]) && s[i])
            syntax_error("syntax error", d);
    }
    else if (s[i] == '<' && s[i])
    {
        i += 2;
        if ((is_symbol(s[i]) && s[i] != '<' && s[i])
            || is_symbol(s[i + 1]))
            syntax_error("syntax error", d);
    }
}