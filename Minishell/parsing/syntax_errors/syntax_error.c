/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:20:24 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/29 23:38:05 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void    handle_pipes(t_token *t, t_data *d)
{
    t_token *p;

    p = ft_lstlast(t);
    if (!ft_strcmp(t->value, "|") || !ft_strcmp(p->value, "|"))
        syntax_error("syntax error", d);
    while (t)
    {
        if (!ft_strcmp(t->value, "|") && !ft_strcmp(t->next->value, "|"))
            syntax_error("syntax error", d);
        t = t->next;
    }
}

void    is_rid_nexto_symbol(t_token *t, t_data *d)
{
    if ((is_one_symbol(t->value, 0) || is_two_symbols(t->value, 0))
        && *t->value != '|')
        if (is_one_symbol(t->next->value, 0)
            || is_two_symbols(t->next->value, 0))
            syntax_error("syntax error", d);
}

void    handle_redirections(t_token *t, t_data *d)
{
    t_token *p;

    p = ft_lstlast(t);
    if (is_symbol(*p->value))
        syntax_error("syntax error laaast", d);
    while (t)
    {
        is_rid_nexto_symbol(t, d);
        t = t->next;
    }
}

void    handle_syntax_error(t_token *t, t_data *d)
{
    handle_pipes(t, d);
    handle_redirections(t, d);
}