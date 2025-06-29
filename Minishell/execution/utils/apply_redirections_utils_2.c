/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_utils_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 23:22:26 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/29 16:04:31 by ielouarr         ###   ########.fr       */
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
	*fd = open(cmd->heredocfilename, O_CREAT | O_RDWR, 0644);
}

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
