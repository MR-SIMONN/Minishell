/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:49 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/04 15:57:14 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	pwd_v(t_data *d)
{
	t_env	*tmp;
	char	cwd[1024];

	tmp = d->env;
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
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		perror("pwd");
	return (0);
}
