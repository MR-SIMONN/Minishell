/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:46:33 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/28 23:59:02 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	apply_redirections(t_str *files)
{
	while (files)
	{
		if ((files->type == APPEND_FILE || files->type == OUT_FILE)
			&& apply_output_redirection(files) != 0)
			return (1);
		if (files->type == IN_FILE && apply_input_redirection(files) != 0)
			return (1);
		files = files->next;
	}
	return (0);
}

void	signal_herdoc(int sig)
{
	(void)sig;
	exit_status(1, 1);
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

int	handle_heredoc_child(t_str *current, int fd, t_data *d)
{
	signal(SIGINT, handle_sigint);
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
	exit(0);
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

int	apply_heredoc(t_cmd *cmd, t_data *d, int index)
{
	t_str	*current;
	int		fd;
	int		status;
	int		pid;

	current = cmd->heredoc_del;
	fd = -1;
	ft_file(cmd, index, d, &fd);
	while (current)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			handle_heredoc_child(current, fd, d);
		else
		{
			if (handle_heredoc_parent(pid, &status) == 130)
			{
				close(fd);
				return (1);
			}
		}
		current = current->next;
	}
	return (close(fd), 0);
}
