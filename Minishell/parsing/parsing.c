/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:59:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/12 06:40:29 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Minishell.h"

int parsing(t_data *d)
{
    if (empty_cmd(d->line))
        return (1);
    if (is_invalid_syntax(d->line, d))
        return (1);
    ft_lst_tokens (d);
    if (handle_syntax_error(d->token, d))
        return (1);
    return (0);
}