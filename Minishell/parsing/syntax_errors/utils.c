/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:14:07 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/12 06:37:40 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int    syntax_error (char *s)
{
    printf ("%s\n", s);
    return (1);
}

int is_symbol(char c)
{
    return(c == '>' || c == '<' || c == '|');
}

int    check_one(char *s, int i)
{
    if (s[i] == '>' && s[i])
    {
        i++;
        if (is_symbol(s[i]) && s[i] != '|' && s[i])
        {
            syntax_error("syntax error");
            return (1);
        }
    }
    if (s[i] == '<' && s[i])
    {
        i++;
        if (is_symbol(s[i]) && s[i] != '>' &&s[i])
        {
            syntax_error("syntax error");
            return (1);
        }
    }
    return (0);
}

int    check_two(char *s, int i)
{
    if (s[i] == '>' && s[i])
    {
        i += 2;
        if (is_symbol(s[i]) && s[i])
        {
            syntax_error("syntax error");
            return (1);
        }
    }
    else if (s[i] == '<' && s[i])
    {
        i += 2;
        if ((is_symbol(s[i]) && s[i] != '<' && s[i])
            || is_symbol(s[i + 1]))
        {
            syntax_error("syntax error");
            return (1);
        }
    }
    return (0);
}
