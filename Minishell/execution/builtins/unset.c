/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:51 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/15 00:09:32 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != '='))
		i++;
	if ((unsigned long)i != ft_strlen(str))
		return (1);
	return (0);
}

int	unset_v(t_data *d, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if ((args[i][0] >= '0' && args[i][0] <= '9')
			|| args[i][ft_strlen(args[i]) - 1] == '!'
				|| is_valid(args[i]) || args[i][0] == '\0')
		{
			ft_putstr_fd("minishell: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("`: not a valid identifier\n", 2);
			i++;
			continue ;
		}
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
