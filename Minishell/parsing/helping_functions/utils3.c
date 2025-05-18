/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:41:57 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/18 11:51:13 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../Minishell.h"

int is_quoted(t_token_type type)
{
    return (type == D_QUOTED || type == S_QUOTED);
}

void    quotes_stuff(char *s, int i, char *c, int *quotes)
{
    if ((s[i] == '\'' || s[i] == '\"') && !*quotes)
    {
        *c = s[i];
        *quotes = 1;
    }
    else if (s[i] == *c && *quotes)
        *quotes = 0;
}