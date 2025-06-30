/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:43 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/30 21:54:06 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	exit_v(char **args, t_data *d)
{
	long	status;
	int		is_out_range;

	1 && (is_out_range = 0, status = 0);
	if (isatty(0) && isatty(1))
		ft_putstr_fd("exit\n", 1);
	if (!args[1])
		free_everything(d, 0);
	if (!is_digit(args[1]))
	{
		num_arg_req(args[1]);
		free_everything(d, 255);
	}
	status = ft_atol(args[1], &is_out_range);
	if (is_out_range)
	{
		num_arg_req(args[1]);
		free_everything(d, 255);
	}
	if (args[2])
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		return ;
	}
	free_everything(d, (unsigned char)status);
}
