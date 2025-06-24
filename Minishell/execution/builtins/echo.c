/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:33 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/23 18:20:00 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int ft_check_option(char **s, int *counter)
{
	int i = 1;
	int j;
	int flag = 1;

	while (s[i])
	{
		if (s[i][0] == '-')
		{
			j = 1;
			while (s[i][j] == 'n')
				j++;
			if (s[i][j] == '\0')
			{
				flag = 0;
				i++;
				continue;
			}
			else
				break;
		}
		else
			break;
	}
	*counter = i;
	return (flag);
}

int echo_v(char **args)
{
	int i = 1;
	int newline = 1;

	if (!args[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}

	if (ft_check_option(args, &i) == 0)
		newline = 0;

	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}

	if (newline)
		ft_putstr_fd("\n", 1);

	return (0);
}