/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_funs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:59:33 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/04 00:53:59 by ielouarr         ###   ########.fr       */
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
void	close_fds_after_use(int in_fd, int pipe_fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (pipe_fd != -1)
		close(pipe_fd);
}
void	prepare_pipe(int *pipe_fd, int need_pipe)
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (need_pipe && pipe(pipe_fd) == -1)
		perror("pipe");
}
void	setup_child_fds(int in_fd, int *pipe_fd)
{
	if (in_fd != STDIN_FILENO && dup2(in_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 in_fd");
		exit(1);
	}
	if (pipe_fd[1] != -1 && dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 pipe_fd[1]");
		exit(1);
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}