/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:45:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/14 20:23:24 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../Minishell.h"

void    check_qoutes(char *s, int *f)
{
    int i;
    char c;

    i = 0;
    while (s[i])
    {
        if ((s[i] == '\'' || s[i] == '\"') && !*f)
        {
            c = s[i];
            *f = 1;
        }
        else if (s[i] == c && *f)
            *f = 0;
        i++;
    }
}
int unclosed_quote(char *s, t_data *d)
{
    int     i;
    int     f;

    if (!s)
        free_everything(d, 1);
    i = 0;
    f = 0;
    check_qoutes(s, &f);
    if (f)
        return (1);
    return (0);
}
int invalid_redirection(char *s)
{
    int     i;
    int     f;
    char    c;
    int     s_e;

    (1) && (i = -1, f = 0, c = 0, s_e = 0);
    while (s && s[++i])
    {
        if ((s[i] == '\'' || s[i] == '\"') && !f)
        {
            c = s[i];
            f = 1;
        }
        else if (s[i] == c && f)
            f = 0;
        if (is_one_symbol(s, i) && s[i] && !f)
            s_e = check_one(s, i);
        else if (is_two_symbols(s, i) && s[i] && !f)
            s_e = check_two(s, i);
        else if ((s[i] == ';' || s[i] == '&') && !f)
            s_e = 1;
        if (s_e)
            return (1);
    }
    return (0);
}

int invalid_pipeout(char *s)
{
    int i;
    int f;

    i = 0;
    f = 0;
    while (s[i] && s[i + 1])
    {
        if (s[i] == '>')
        {
            if (s[i + 1] == '>' || s[i + 1] == '|')
                i+=2;
            else
            {
                f = 1;
                i++;
            }
        }
        if (s[i] && s[i] == '|' && f)
        {
            printf("\npipe out :)\n");
            return (1);
        }
        else
        {
            i++;
            f = 0;
        }
    }
    return (0);
}

int is_invalid_syntax(char *s, t_data *d)
{
    if (!s)
        free_everything(d, 1);
    if (unclosed_quote(s, d))
        return (1);
    if (invalid_redirection(s))
        return (1);
    if (invalid_pipeout(s))
        return (1);
    return (0);
}
