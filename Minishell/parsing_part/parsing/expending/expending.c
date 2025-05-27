/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:19:40 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/27 20:40:35 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"


void    expend_it(t_token *t, char *key, int index, t_data *d)
{
    int len;

    if (!var_value(d->env, key))
        return;
    while (t->value[index] && valid_char(t->value[index]))
        index++;
    len = expended_token_len(d->env, t->value, key, index);
    printf ("\nlen is ---->   %d\n", len);
    t->value = new_expended_token(t->value, var_value(d->env, key), len, d);
}

char    *delete_invalid_var(t_token *t, t_data *d)
{
    int     i;
    int     j;
    int     len;
    char    *s;
    int     flag;

    i = 0;
    j = 0;
    flag = 0;
    len = decrease_len(t);
    s = ft_malloc(len + 1, d);
    while (t->value[i])
    {
		if (t->value[i] == '$' && !flag)
		{
			i++;
			while (t->value[i] && valid_char(t->value[i]))
				i++;
			flag = 1;
		}
		else if(t->value[i])
            s[j++] = t->value[i++];
    }
    return (s[j] = '\0', s);
}

void    check_var(t_token *t, int i, t_data *d)
{
    char    *s;

    printf("%s\n\n", t->value);
    s = copy_var_name(t->value, i + 1, d);
    printf(" key ----> %s\n", s);
    if (valid_var(s, d->env))
    {
        printf("ggg\n\n");
        expend_it(t, s, i + 1, d);
    }
    else
        t->value = delete_invalid_var(t, d);
}

void    expending(t_token *t, t_data *d)
{
    int i;

    while (t)
    {
        i = 0;
        if (t->type == VAR && var_count(t->value) > 0)
        {
            while (t->value[i])
            {
                // printf ("\n%d\n", var_count(t->value));
                // exit (0);
                // skip_dollar_sign(t->value, &i);
                if (t->value[i] && t->value[i] == '$' && is_var(t->value[i + 1]))
                    check_var(t, i, d);
                else
                    i++;
            }
        }
        t = t->next;
    }
}
