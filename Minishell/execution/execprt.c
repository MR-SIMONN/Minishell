/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execprt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:19:01 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/17 21:30:47 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	duping(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	count_commands(t_cmd *cmds)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmds;
	while (current)
	{
		count++;
		if (current->pipe == 0)
			break ;
		current = current->next;
	}
	return (count);
}

void	ft_has_no_pipe(t_data *d)
{
	int	execute;

	if (is_builtin(d->cmds->cmd) == 0)
	{
		execute_single_builtin(d->cmds, &execute, d);
		exit_status(1, execute);
		return ;
	}
	execute_single_external(d->cmds, &execute, d);
	exit_status(1, execute);
}
