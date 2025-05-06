/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:45:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/06 03:28:53 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../Minishell.h"

int unclosed_quote(char *s, t_data *d)
{
    int i;
    int f;
    char c;

    i = 0;
    f = 0;
    if (!s)
        free_everything(d, 1);
    while (s[i])
    {
        if ((s[i] == '\'' || s[i] == '\"') && !f)
        {
            c = s[i];
            f = 1;
        }
        else if (s[i] == c && f)
            f = 0;
        i++;
    }
    if (f)
    {
        syntax_error("syntax error unclosed quotes", d);
        return (1);
    }
    return (0);
}
int invalid_redirection(char *s, t_data *d)
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
            s_e = check_one(s, i, d);
        else if (is_two_symbols(s, i) && s[i] && !f)
            s_e = check_two(s, i, d);
        else if (s[i] == ';' && !f)
            s_e = syntax_error("syntax error `;`", d);
        if (s_e)
            return (1);
    }
    return (0);
}
int is_invalid_syntax(char *s, t_data *d)
{
    if (!s)
        free_everything(d, 1);
    if (unclosed_quote(s, d))
        return (1);
    if (invalid_redirection(s, d))
        return (1);
    return (0);
}