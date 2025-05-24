/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:42:05 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/24 15:16:28 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void    set_strcut_values(t_data *d)
{
    d->line = NULL;
    d->heap = NULL;
    d->token = NULL;
    d->cmds = NULL;
    d->env = NULL;
    d->exp = NULL;
}