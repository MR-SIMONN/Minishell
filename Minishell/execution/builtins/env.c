/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:36 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/17 21:31:25 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	env_v(t_env *list, char **args)
{
	t_env	*tmp;

	if (args[1])
	{
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(args[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		return (127);
	}
	tmp = list;
	while (tmp)
	{
		if (tmp->both && ft_strchr(tmp->both, '='))
		{
			ft_putstr_fd(tmp->both, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

