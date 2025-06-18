/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/18 19:24:50 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

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

static pid_t	fork_and_execute(t_cmd *current, t_env **env, t_data *d,
					int pipes[][2], int i, int cmd_count)
{
	pid_t	pid;
	t_fds	fds;
	int		input_fd;
	int		output_fd;

	pid = fork();
	if (pid == 0)
	{
		fds = setup_pipe_fds(pipes, i, cmd_count);
		input_fd = fds.input_fd;
		output_fd = fds.output_fd;
		close_pipes_in_child(pipes, cmd_count, i);
		exit(execute_single_cmd(current, env, d, input_fd, output_fd));
	}
	else if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	current = current->next;
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

int	execute_pipeline_commands(t_env **env, t_cmd *cmds, t_data *d,
				int cmd_count)
{
	int		pipes[cmd_count - 1][2];
	pid_t	pids[cmd_count];
	t_cmd	*current;
	int		i;

	if (create_pipes(pipes, cmd_count) != 0)
		return (1);
	current = cmds;
	i = 0;
	while (i < cmd_count && current)
	{
		pids[i] = fork_and_execute(current, env, d, pipes, i, cmd_count);
		if (pids[i] == -1)
			return (1);
		if (current->pipe == 0)
			break ;
		current = current->next;
		i++;
	}
	close_all_pipes(pipes, cmd_count);
	return (wait_for_children(pids, cmd_count));
}

int	execution(t_env **env, t_cmd *cmds, t_data *d)
{
	return (execute_pipeline(env, cmds, d));
}