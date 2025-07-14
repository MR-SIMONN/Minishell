/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:42:05 by moel-hai          #+#    #+#             */
/*   Updated: 2025/07/14 22:28:58 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	set_strcut_values(t_data *d, int i)
{
	if (i == 0)
	{
		d->line = NULL;
		d->heap = NULL;
		d->token = NULL;
		d->cmds = NULL;
		d->env = NULL;
		d->exp = NULL;
		d->backup_pwd = NULL;
	}
	else
	{
		d->line = NULL;
		d->token = NULL;
		d->cmds = NULL;
	}
}
