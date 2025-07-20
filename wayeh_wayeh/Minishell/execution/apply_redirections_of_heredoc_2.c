/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_of_heredoc_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:54:46 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/16 20:29:18 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	closeall(void)
{
	int	i;

	i = 3;
	while (i <= OPEN_MAX)
	{
		close(i);
		i++;
	}
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
		d->line = readline("> ");
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

	current = d->cmds;
	while (current)
	{
		if (current->heredoc && current->heredoc_del != NULL)
		{
			current->fd_heredoc = -1;
			if (apply_heredoc(current, d) != 0)
				return (1);
		}
		current = current->next;
	}
	return (0);
}

int	apply_heredoc_redirection(t_cmd *cmd)
{
	int	fd;

	if (cmd->heredoc && cmd->heredoc_del != NULL)
	{
		fd = dup(cmd->fd_heredoc);
		if (fd == -1)
		{
			perror("dup");
			return (1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror(cmd->heredocfilename);
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}
