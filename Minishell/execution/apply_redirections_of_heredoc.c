/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_of_heredoc.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:46:33 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/16 13:14:14 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	signal_herdoc(int sig)
{
	(void)sig;
	exit_status(1, 1);
	ft_putstr_fd("\n", 1);
	exit(130);
}

int	forking_for_heredoc(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}

int	heredoc_child_part(int fd, int pid, int *status)
{
	close(fd);
	if (handle_heredoc_parent(pid, status) == 130)
		return (closeall(), 1);
	return (0);
}

int	apply_heredoc(t_cmd *cmd, t_data *d)
{
	t_str	*current;
	int		fd;
	int		status;
	int		pid;

	current = cmd->heredoc_del;
	fd = -1;
	while (current)
	{
		signal(SIGINT, SIG_IGN);
		ft_file(cmd, d, &fd);
		pid = forking_for_heredoc();
		if (pid == 0)
		{
			close(cmd->fd_heredoc);
			signal(SIGINT, signal_herdoc);
			free_everything(d, handle_heredoc_child(current, fd, d));
		}
		else
			if (heredoc_child_part(fd, pid, &status) != 0)
				return (1);
		current = current->next;
	}
	return (close(fd), 0);
}
