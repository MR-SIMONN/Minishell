/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:36 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/28 22:17:04 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	env_v(t_env *list, char **args)
{
	t_env	*tmp;

	if (args[1])
	{
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(args[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		exit_status(1, 127);
		return ;
	}
	tmp = list;
	while (tmp)
	{
		ft_putstr_fd(tmp->both, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}
