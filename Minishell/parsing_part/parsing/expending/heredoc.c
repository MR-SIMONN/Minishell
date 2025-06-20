/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:10:31 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/13 21:39:53 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

void    expend_var(char **str, char *key, int index, t_data *d)
{
    t_expend_infos  infos;

    if (!var_value(d->env, key, d))
        return ;
    if (key[0] == '?')
        index++;
    else
        while ((*str)[index] && valid_char((*str)[index]))
            index++;
    infos.s = *str;
    infos.env_value = var_value(d->env, key, d);
    infos.d = d;
    infos.after_key = index;
    infos.key = key;
    infos.len = expended_token_len(d, *str, key, index);
    *str = new_expended_token(infos);
}

void    check_heredoc_var(char **str, int i, t_data *d)
{
    char    *s;

    s = copy_var_name(*str, i + 1, d);
    if (valid_var(s, d->env))
        expend_var(str, s, i + 1, d);
    else
        *str = delete_invalid_var(*str, d);
}

char    *expand_heredoc(char *s, t_data *d)
{
    int i;

    i = 0;
    if (var_count(s) == 0)
        return (s);
    while (s[i] && var_count(s) > 0)
    {
        if (s[i] && s[i] == '$'
            && is_var(s[i + 1]))
            check_heredoc_var(&s, i, d);
        else
            i++;
    }
    return (s);
}
