/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:10:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/11 02:06:07 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void    copy_args(char **args, t_token *t, t_data *d)
{
    int i;
    int before_reds;

    i = 0;
    before_reds = 1;
    while (t)
    {
        if (t->type == PIPE)
            return ;
        if (t->type == WORD && before_reds)
            args[i++] = ft_strdup(t->value, d);
        else if (t->value && t->next && is_symbol(*t->value))
        {
            before_reds = 0;
            if (t->next->next && t->next->next->type == WORD)
                args[i++] = ft_strdup(t->next->next->value, d);
        }
        t = t->next;
    }
    args[i] = 0;
}
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
        else if (t->value && t->next && is_symbol(*t->value))
        {
            before_reds = 0;
            if (t->next->next && t->next->next->type == WORD)
                len++;
        }
        t = t->next;
    }
    return (len);
}
