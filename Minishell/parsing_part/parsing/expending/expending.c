/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:19:40 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/21 16:41:51 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

void    expend_it(t_token *t, char *key, int index, t_data *d)
{
    int len;

    while (t->value[index] && !valid_char(t->value[index]))
        index++;
    len = expended_token_len(d->env, t->value, key, index) + 1;
    t->value = new_expended_token(t->value, var_value(d->env, key), len, d);
}

void    check_var(t_token *t, int i, t_data *d)
{
    char    *s;
    
    s = copy_var(t->value, i, d);
    if (valid_var(s, d->env))
        expend_it(t, s, i, d);
    else
        t->type = IGNORED;
}

void    expending(t_token *t, t_data *d)
{
    int i;

    i = 0;
    while (t)
    {
        if (t->type == VAR)
        {
            skip_it(t->value, &i, ' ');
            if (t->value[i] == '$')
                check_var(t, ++i, d);
            // else//which means there is a string befor a var
            //     ;
        }
        t = t->next;
    }
}
