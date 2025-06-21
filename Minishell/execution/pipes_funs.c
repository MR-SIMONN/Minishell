/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_funs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:26:39 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/18 19:24:03 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	has_pipeline(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (current->pipe == 1)
			return (1);
		current = current->next;
	}
	return (0);
}

int	create_pipes(int pipes[][2], int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (1);
		}
		i++;
	}
	return (0);
}

void	close_pipes_in_child(int pipes[][2], int cmd_count, int cmd_index)
{
	int	j;

	j = 0;
	while (j < cmd_count - 1)
	{
		if (j != cmd_index - 1)
			close(pipes[j][0]);
		if (j != cmd_index)
			close(pipes[j][1]);
		j++;
	}
}

void	close_all_pipes(int pipes[][2], int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

t_fds	setup_pipe_fds(int pipes[][2], int cmd_index, int cmd_count)
{
	t_fds	fds;

	fds.input_fd = STDIN_FILENO;
	fds.output_fd = STDOUT_FILENO;
	if (cmd_index > 0)
		fds.input_fd = pipes[cmd_index - 1][0];
	if (cmd_index < cmd_count - 1)
		fds.output_fd = pipes[cmd_index][1];
	return (fds);
}