/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:42:05 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/12 17:17:39 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void    set_strcut_values(t_data *d, int i)
{
    if (i == 0)
    {
        d->line = NULL;
        d->heap = NULL;
        d->token = NULL;
        d->cmds = NULL;
        d->env = NULL;
        d->exp = NULL;
        d->exit_value = 0;
    }
    else
    {
        d->line = NULL;
        d->heap = NULL;
        d->token = NULL;
        d->cmds = NULL;
    }
}
