/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:15:36 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/17 21:28:32 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "echo") == 0)
		return (0);
	return (1);
}

int	execute_builtin(char *cmd, char **args, t_data *d)
{
	int	return_value;

	return_value = 0;
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return_value = env_v(d->env, args);
	else if (ft_strcmp(cmd, "cd") == 0)
		return_value = cd_v(args, d);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return_value = pwd_v(d);
	else if (ft_strcmp(cmd, "unset") == 0)
		return_value = unset_v(d, args);
	else if (ft_strcmp(cmd, "export") == 0)
		return_value = export_v(d, args);
	else if (ft_strcmp(cmd, "echo") == 0)
		return_value = echo_v(args);
	else if (ft_strcmp(cmd, "exit") == 0)
		exit_v(args, d);
	return (return_value);
}
