/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:51 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/29 15:05:09 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	unset_v(t_data *d, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "_") == 0)
		{
			i++;
			continue ;
		}
		remove_from_env_lst(&d->env, args[i]);
		remove_from_export_lst(&d->exp, args[i]);
		i++;
	}
	return (0);
}
