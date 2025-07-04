/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/04 05:12:22 by ielouarr         ###   ########.fr       */
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
		setup_child_fds(in_fd, pipe_fd);
		free_everything(d, execute_single_cmd(cmd, d, (t_fds){STDIN_FILENO, STDOUT_FILENO}));
	}
	return (pid);
}

int	wait_for_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	final_status;

// signal(SIGINT,SIG_IGN);
// 		waitpid(pid, &status, 0);
// 		signal(SIGINT,handle_sigint);
// 		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
//     		exit_status(1, 130);
// 		else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
//     		exit_status(1, 131);
// 	final_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
			final_status = WEXITSTATUS(status);
		i++;
	}
	return (final_status);
}

void	wait_childrens(pid_t *pids, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
}

int	execute_pipeline_commands(t_data *d, int cmd_count)
{
	t_cmd	*current;
	pid_t	*pids;
	int		pipe_fd[2];
	int		in_fd;
	int		i;

	current = d->cmds;
	pids = ft_malloc(sizeof(pid_t) * cmd_count, d);
	1 && (i = 0, in_fd = STDIN_FILENO);
	while (current && i < cmd_count)
	{
		prepare_pipe(pipe_fd, current->pipe);
		if (pipe_fd[0] == -1 && pipe_fd[1] == -1 && current->pipe == 1)
			return (wait_childrens(pids, i), 1);
		pids[i] = fork_child_and_execute(current, d, in_fd, pipe_fd);
		if (pids[i] == -1)
			return (wait_childrens(pids, i), 1);
		close_fds_after_use(in_fd, pipe_fd[1]);
		in_fd = pipe_fd[0];
		current = current->next;
		i++;
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	return (wait_for_children(pids, cmd_count));
}

int	execution(t_data *d)
{
	struct termios	tty;
	int				status;

	tcgetattr(STDIN_FILENO, &tty);
	status = execute_pipeline(d);
	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
	return (status);
}
