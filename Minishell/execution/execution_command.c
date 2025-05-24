/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:43:49 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/23 22:40:17 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	execution(t_env **env, t_cmd *cmds, t_data *d)
{
	if(is_builtin(cmds->cmd) == 0 && cmds->pipe == 0)
	{
		// apply_redirection();
		if(execute_builtin(cmds->cmd, env, cmds->args, d) != 0)
			return (1);
	}
	return (0);
}