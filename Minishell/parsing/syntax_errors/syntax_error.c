/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:20:24 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/27 22:58:08 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

// syntax error near unexpected token `|'


// 🏀 --> Group 1: Pipe errors (|)
// 👉 Pipes must be between two valid commands.

// Pipe at start.					---> ✅

// Pipe at end.					    ---> ✅

// Pipe next to another pipe.       ---> ✅

// 🚨 message to printf : "syntax error near unexpected token `|`" 🚨


// 🏀 ---> Group 2: Redirection errors (<, >, >>, <<)
// 👉 Redirections must be followed by a valid file/token.

// Redirection at end.		STR = "newline"							--->

// Redirection followed by another symbol.	STR = the second symbol	--->

// 🚨 message to printf : "syntax error near unexpected token `$STR'" 🚨

void    handle_pipes(t_token *t, t_data *d)
{
    t_token *p;

    p = ft_lstlast(t);
    if (!ft_strcmp(t->value, "|") || !ft_strcmp(p->value, "|"))
        syntax_error("syntax error near unexpected token `|`", d);
    while (t)
    {
        if (!ft_strcmp(t->value, "|") && !ft_strcmp(t->next->value, "|"))
            syntax_error("syntax error near unexpected token `|`", d);
        t = t->next;
    }
}

void    handle_syntax_error(t_token *t, t_data *d)
{
    handle_pipes(t, d);
    // handle_redirections(t, d);
}