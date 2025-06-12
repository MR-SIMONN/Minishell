/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 00:46:30 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/05 00:50:08 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

    // if ((t[i][0] == '\'' && t[i][ft_strlen(t[i]) - 1] == '\'') 
    //     || (t[i][0] == '\"' && t[i][ft_strlen(t[i]) - 1] == '\"'))
    //     t[i] = delete_quotes(t[i], d);
    // else
    //     t[i] = delete_random_quotes(t[i], d);


char    *delete_random_quotes(char *s, t_data *d)
{
    int i;
    int j;
    int len;
    char *str;

    i = 0;
    j = 0;
    len = ft_strlen(s) - quotes_len(s);
    str = ft_malloc(len + 1, d);
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '\"')
            i++;
        if (s[i])
            str[j++] = s[i++];
    }
    return (str[j] = '\0', str);
}

char    *delete_quotes(char *s, t_data *d)
{
    int     i;
    int     j;
    int     len;
    char    *str;
    char    c;

    i = 1;
    j = 0;
    len = ft_strlen(s) - 2;
    str = ft_malloc(len + 1, d);
    c = s[0];
    while (s[i + 1])
    {
        if (s[i] != c)
            str[j++] = s[i];
        i++;
    }
    str[j] = '\0';
    return (str);
}
void    get_rid_of_quotes(t_token *t, t_data *d)
{
    while (t)
    {
        if ((t->value[0] == '\'' && t->value[ft_strlen(t->value) - 1] == '\'') 
            || (t->value[0] == '\"' && t->value[ft_strlen(t->value) - 1] == '\"'))
            t->value = delete_quotes(t->value, d);
        else
            t->value = delete_random_quotes(t->value, d);
        t = t->next;
    }
}