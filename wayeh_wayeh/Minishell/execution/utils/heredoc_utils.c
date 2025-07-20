/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 23:29:55 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/16 03:00:48 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	ft_file(t_cmd *cmd, t_data *d, int *fd)
{
	cmd->heredocfilename = ft_strdup("/tmp/.heredoc", d);
	if (*fd != -1)
		unlink(cmd->heredocfilename);
	*fd = open(cmd->heredocfilename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->fd_heredoc != -1)
		close(cmd->fd_heredoc);
	cmd->fd_heredoc = open(cmd->heredocfilename, O_RDONLY, 0666);
	unlink(cmd->heredocfilename);
}

void	ft_expand_heredoc_handler(t_str *current, int fd, t_data *d)
{
	char	*exp;

	if (current->expendable != 0)
	{
		exp = expand_heredoc(d->line, d);
		ft_putstr_fd(exp, fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		ft_putstr_fd(d->line, fd);
		ft_putstr_fd("\n", fd);
	}
}
