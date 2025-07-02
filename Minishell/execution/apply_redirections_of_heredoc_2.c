/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_of_heredoc_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:54:46 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/02 13:07:49 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_check_heredoc_multp(t_str *current)
{
	int	count;

	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count > 1);
}

int	ft_dupone_heredocase(int output_fd)
{
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			return (1);
		}
		close(output_fd);
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
