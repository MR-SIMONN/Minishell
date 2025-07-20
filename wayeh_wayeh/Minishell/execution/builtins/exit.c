/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:43 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/20 13:52:24 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	exit_v(char **args, t_data *d)
{
	long	status;
	int		is_out_range;

	is_out_range = 0;
	status = 0;
	if (!d->cmds->pipe && isatty(0))
		ft_putstr_fd("exit\n", 2);
	if (!args[1])
	{
		if (!d->cmds->pipe && isatty(0))
			free_everything(d, exit_status(0, 0));
		exit(0);
	}
	if (is_digit(args[1]) && num_arg_req(args[1]))
		free_everything(d, 255);
	status = ft_atol(args[1], &is_out_range);
	if (is_out_range && num_arg_req(args[1]))
		free_everything(d, 255);
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit_status(1, 1);
		return ;
	}
	free_everything(d, (unsigned char)status);
}
