/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:54:46 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/29 10:57:47 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	setup_redirections(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		if (ft_input_fd(input_fd) != 0)
			return (1);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (ft_output_fd(output_fd) != 0)
			return (1);
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
		}
		index++;
		current = current->next;
	}
	return (0);
}

void	unlink_all_heredocfiles(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->heredoc && cmds->heredoc_del != NULL)
			unlink(cmds->heredocfilename);
		cmds = cmds->next;
	}
}

int	apply_heredoc_redirection(t_cmd *cmd)
{
	int	fd;

	if (cmd->heredoc && cmd->heredoc_del != NULL)
	{
		fd = open(cmd->heredocfilename, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->heredocfilename);
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

int	handling_heredocs(t_cmd *cmd, int input_fd, int output_fd)
{
	int		has_multiple_heredocs;
	t_str	*current;

	has_multiple_heredocs = 0;
	if (cmd->heredoc_del)
	{
		current = cmd->heredoc_del;
		has_multiple_heredocs = ft_check_heredoc_multp(current);
	}
	if (has_multiple_heredocs || (cmd->heredoc == 0))
	{
		if (setup_redirections(input_fd, output_fd) != 0)
			return (1);
	}
	else
	{
		if (ft_dupone_heredocase(output_fd) != 0)
			return (1);
	}
	return (0);
}
