/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:43:49 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/13 11:15:33 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int execution(t_env **env, t_cmd *cmds, t_data *d)
{
	if (is_builtin(cmds->cmd) == 0 && cmds->pipe == 0)
	{
		int saved_stdin;
		int saved_stdout;
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
	
		if (apply_redirection(cmds, d) != 0)
		{
			duping(saved_stdin,saved_stdout);
			return (1);
		}

		if (execute_builtin(cmds->cmd, env, cmds->args, d) != 0)
		{
			duping(saved_stdin,saved_stdout);
			return (1);
		}
		duping(saved_stdin,saved_stdout);
	}
	return (0);
}
