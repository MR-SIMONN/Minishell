/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:10:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/11 01:12:37 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int args_len(t_token *t)
{
    int len;
    int before_reds;

    len = 0;
    before_reds = 1;
    while (t)
    {
        if (t->type == PIPE)
            return (len);
        if (t->type == WORD && before_reds)
            len++;
        else if (is_symbol(*t->value) && t->next)
        {
            before_reds = 0;
            if (t->next->next && t->next->next->type == WORD)
                len++;
        }
        t = t->next;
    }
    return (len);
}
