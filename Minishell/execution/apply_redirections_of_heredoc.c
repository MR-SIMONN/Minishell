/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_of_heredoc.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:46:33 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/14 12:03:25 by ielouarr         ###   ########.fr       */
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

int	handle_heredoc_child(t_str *current, int fd, t_data *d)
{
	if (fd < 0)
	{
		perror("open .heredoc file");
		return (1);
	}
	while (1)
	{
		d->line = readline(">");
		if (!d->line || ft_strcmp(current->s, d->line) == 0)
		{
			free(d->line);
			d->line = NULL;
			break ;
		}
		ft_expand_heredoc_handler(current, fd, d);
		free(d->line);
		d->line = NULL;
	}
	return (0);
}

int	handle_heredoc_parent(int pid, int *status)
{
	waitpid(pid, status, 0);
	signal(SIGINT, handle_sigint);
	if (WIFEXITED(*status) && WEXITSTATUS(*status) == 130)
	{
		exit_status(1, 1);
		return (130);
	}
	return (0);
}

int	process_heredocs_before_fork(t_data *d)
{
	t_cmd	*current;
	int		index;

	current = d->cmds;
	index = 0;
	while (current)
	{
		if (current->heredoc && current->heredoc_del != NULL)
		{
			if (apply_heredoc(current, d, index) != 0)
				return (1);
			index++;
		}
		current = current->next;
	}
	return (0);
}

int	apply_heredoc(t_cmd *cmd, t_data *d, int index)
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
		pid = fork();
		ft_file(cmd, index, d, &fd);
		if (pid == 0)
		{
			signal(SIGINT, signal_herdoc);
			free_everything(d, handle_heredoc_child(current, fd, d));
		}
		else
			if (handle_heredoc_parent(pid, &status) == 130)
				return (close(fd), 1);
		close(fd);
		current = current->next;
	}
	return (close(fd), 0);
}
