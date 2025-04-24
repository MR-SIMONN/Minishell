/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:31:34 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/24 21:32:26 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void handle_symbols(char *s, int *len, int i)
{
    if (i > 0 && s[i - 1] != ' ')
        (*len)++;
    if (s[i + 2] && s[i + 2] != ' ')
        (*len)++;
}

int is_two_symbols(char *s, int i)
{
    return (s[i] && s[i + 1] &&
            ((s[i] == '>' && s[i + 1] == '>') ||
             (s[i] == '<' && s[i + 1] == '<')));
}

int is_one_symbol(char *s, int i)
{
    return (s[i] == '|' ||
           (s[i] == '>' && s[i + 1] != '>') ||
           (s[i] == '<' && s[i + 1] != '<'));
}