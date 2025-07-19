/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/19 20:15:58 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static pid_t	fork_child_and_execute(t_cmd *cmd, t_data *d,
		int in_fd, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (setup_child_fds(in_fd, pipe_fd) != 0)
			free_everything(d, 1);
		free_everything(d, execute_single_cmd(cmd, d,
				(t_fds){STDIN_FILENO, STDOUT_FILENO}));
	}
	return (pid);
}

int	func(pid_t *pids, int i, int *return_value)
{
	closeall();
	wait_children(pids, i);
	*return_value = 1;
	return (1);
}

int	prepare_curr_pipe(int *pipe_fd, t_cmd *current)
{
	prepare_pipe(pipe_fd, current->pipe);
	if (pipe_fd[0] == -1 && pipe_fd[1] == -1 && current->pipe == 1)
		return (1);
	return (0);
}

void	execute_pipeline_commands(t_data *d, int *return_value, int cmd_count)
{
	t_cmd	*current;
	pid_t	*pids;
	int		pipe_fd[2];
	int		in_fd;
	int		i;

	1 && (current = d->cmds, i = 0, in_fd = STDIN_FILENO);
	pids = ft_malloc(sizeof(pid_t) * cmd_count, d);
	while (current && i < cmd_count)
	{
		if (prepare_curr_pipe(pipe_fd, current) && func(pids, i, return_value))
			return ;
		pids[i] = fork_child_and_execute(current, d, in_fd, pipe_fd);
		if (pids[i] == -1 && func(pids, i, return_value))
			return ;
		close_fds_after_use(in_fd, pipe_fd[1]);
		in_fd = pipe_fd[0];
		current = current->next;
		i++;
	}
	wait_for_children(pids, return_value, cmd_count);
	closeall();
}

void	execution(t_data *d)
{
	struct termios	tty;

	tcgetattr(STDIN_FILENO, &tty);
	execute_pipeline(d);
	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
