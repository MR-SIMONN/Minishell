/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:47:38 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/12 17:18:34 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

char    *var_value(t_env *env, char *key, t_data *d)
{
    if (key[0] == '?')
        return (ft_itoa(d->exit_value, d));
    while (env)
    {
        if (!ft_strcmp(key, env->key))
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

char    *new_expended_token(t_expend_infos  infos)
{
    int     i;
    int     j;
    int     after_var;
    char    *str;

    i = 0;
    j = 0;
    after_var = infos.after_key - ft_strlen(infos.key) - 1;
    str = ft_malloc(infos.len + 1, infos.d);
    while (infos.s[i] && i < after_var)
        str[j++] = infos.s[i++];
    after_var = infos.after_key - ft_strlen(infos.key);
    if (infos.s[after_var] == '?')
        after_var++;
    else
        while (infos.s[after_var] && valid_char(infos.s[after_var]))
            after_var++;
    i = 0;
    while (infos.env_value && infos.env_value[i])
        str[j++] = infos.env_value[i++];
    while (infos.s[after_var])
        str[j++] = infos.s[after_var++];
    return (str[j] = '\0', str);
}

int expended_token_len(t_data *d, char *s, char *key, int i)
{
    int var_len;
    int after_len;
    int before_len;

    before_len = i - ft_strlen(key) - 1;
    after_len = 0;
    var_len = ft_strlen(var_value(d->env, key, d));
    while (s[i])
    {
        i++;
        after_len++;
    }
    return (before_len + var_len + after_len);
}

char    *copy_var_name(char *s, int i, t_data *d)
{
    int     len;
    int     j;
    char    *str;

    if (s[i] == '?')
        return (ft_strdup("?", d));
    len = 0;
    j = i;
    while (s[j] && valid_char(s[j]))
    {
        j++;
        len++;
    }
    str = ft_malloc(len + 1, d);
    j = 0;
    while (s[i] && valid_char(s[i]))
        str[j++] = s[i++];
    return (str[j] = '\0', str);
}
int valid_var(char *s, t_env *env)
{
    if (s[0] == '?')
        return (1);
    while (env)
    {
        if (!ft_strcmp(s, env->key))
            return (1);
        env = env->next;
    }
    return (0);
}