/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:14:07 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/22 22:06:05 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

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
            return (1);
    }
    if (s[i] && s[i] == '<')
    {
        i++;
        if (is_symbol(s[i]) && s[i] != '>' &&s[i])
            return (1);
    }
    if (s[i] && s[i + 1] && s[i] == '|')
    {
        if (s[i + 1] == '|')
            return (1);
    }
    return (0);
}

int    check_two(char *s, int i)
{
    if (s[i] == '>' && s[i])
    {
        i += 2;
        if (is_symbol(s[i]) && s[i])
            return (1);
    }
    else if (s[i] == '<' && s[i])
    {
        i += 2;
        if (s[i] && is_symbol(s[i]))
            return (1);
    }
    return (0);
}

int no_pipeout_token(t_token *t)
{
    if (!t)
        return (1);
    if (t->type == REDIRECT_OUT && t->next->type == PIPE)
        return (0);
    return (1);
}