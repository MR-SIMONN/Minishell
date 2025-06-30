/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/30 19:45:42 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static pid_t	fork_and_execute(t_cmd *current, t_data *d, int i,
			int cmd_count)
{
	pid_t	pid;
	t_fds	fds;

	pid = fork();
	if (pid == 0)
	{
		fds = setup_pipe_fds(d->pipes, i, cmd_count);
		close_pipes_in_child(d->pipes, cmd_count, i);
		exit(execute_single_cmd(current, d, fds));
	}
	else if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

int	wait_for_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	final_status;

	final_status = 0;
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
	pid_t	*pids;
	t_cmd	*current;
	int		i;

	i = 0;
	pids = ft_malloc (sizeof(pid_t) * cmd_count, d);
	if (create_pipes(d, cmd_count) != 0)
		return (1);
	current = d->cmds;
	while (i < cmd_count && current)
	{
		pids[i] = fork_and_execute(current, d, i, cmd_count);
		if (pids[i] == -1)
		{
			wait_childrens(pids, i);
			close_all_pipes(d->pipes, cmd_count);
			return (1);
		}
		if (current->pipe == 0)
			break ;
		current = current->next;
		i++;
	}
	close_all_pipes(d->pipes, cmd_count);
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
