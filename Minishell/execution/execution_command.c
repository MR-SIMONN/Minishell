/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:43:49 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/15 22:44:55 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int execution(t_env **env, t_cmd *cmds, t_data *d)
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
	if (is_builtin(cmds->cmd) == 0 && cmds->pipe == 0)
	{
		

		if (execute_builtin(cmds->cmd, env, cmds->args, d) != 0)
		{
			duping(saved_stdin,saved_stdout);
			return (1);
		}
		duping(saved_stdin,saved_stdout);
	}
	else
	{
		char **str = get_path(*env, d);
		if (!str)
		{
    		ft_putstr_fd("minishell: command not found\n", 2);
   			return (1);
		}
		char *path = right_path(str, cmds, d);
		if(path)
			ft_putstr_fd("command found\n", 1);
		duping(saved_stdin,saved_stdout);
	}
	return (0);
}
