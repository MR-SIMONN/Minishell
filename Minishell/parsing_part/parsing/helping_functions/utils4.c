/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:47:38 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/29 14:30:26 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

char    *var_value(t_env *env, char *key)
{
    while (env)
    {
        if (!ft_strcmp(key, env->key))
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

char    *new_expended_token(char *s, char *env_value, int len, t_data *d, int after_key, char *key)
{
    int     i;
    int     j;
    int     after_var;
    char    *str;

    i = 0;
    j = 0;
    after_var = after_key - ft_strlen(key) - 1;
    str = ft_malloc(len + 1, d);
    while (s[i] && i < after_var)
        str[j++] = s[i++];
    after_var = after_key - ft_strlen(key);
    while (s[after_var] && valid_char(s[after_var]))
        after_var++;
    i = 0;
    while (env_value && env_value[i])
        str[j++] = env_value[i++];
    while (s[after_var])
        str[j++] = s[after_var++];
    return (str[j] = '\0', str);
}

int expended_token_len(t_env *env, char *s, char *key, int i)
{
    int var_len;
    int after_len;
    int before_len;

    before_len = i - ft_strlen(key) - 1;
    after_len = 0;
    var_len = ft_strlen(var_value(env, key));
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
    while (env)
    {
        if (!ft_strcmp(s, env->key))
        {
            printf("valid\n");
            return (1);
        }
        env = env->next;
    }
    printf("not valid\nremoved\n\n");
    return (0);
}