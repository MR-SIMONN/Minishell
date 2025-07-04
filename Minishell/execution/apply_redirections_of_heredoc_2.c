/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_of_heredoc_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:54:46 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/03 22:43:00 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

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

