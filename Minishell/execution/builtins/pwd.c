/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:49 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/14 22:44:20 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	pwd_v(t_data *d)
{
	t_env	*tmp;
	char	cwd[1024];

	tmp = d->env;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0 && tmp->value)
		{
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
		tmp = tmp->next;
	}
	ft_putstr_fd(d->backup_pwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
