/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_utils_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 23:29:55 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/30 17:59:18 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	ft_file(t_cmd *cmd, int index, t_data *d, int *fd)
{
	char	*filename;
	char	*num;

	num = ft_itoa(index, d);
	filename = ft_strjoin(".heredoc_", num, d);
	cmd->heredocfilename = ft_strdup(filename, d);
	unlink(cmd->heredocfilename);
	*fd = open(cmd->heredocfilename, O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void	ft_expand_heredoc_handler(t_str *current, int fd, t_data *d)
{
	char	*exp;

	if (current->expendable != 0)
	{
		exp = expand_heredoc(d->line, d);
		ft_putstr_fd(exp, fd);
		ft_putstr_fd("\n", fd);
		if (exp != d->line)
			free(exp);
	}
	else
	{
		ft_putstr_fd(d->line, fd);
		ft_putstr_fd("\n", fd);
	}
}
