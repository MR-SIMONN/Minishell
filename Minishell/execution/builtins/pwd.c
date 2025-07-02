/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:49 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/02 16:31:28 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	pwd_v(t_data *d)
{
	t_env *tmp;

	tmp = d->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
			break;
		}
		tmp = tmp->next;
	}
	return (0);
}
