/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_funs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:41:14 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/04 16:43:30 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	wait_for_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	final_status;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
			final_status = WEXITSTATUS(status);
		i++;
	}
	return (final_status);
}

void	wait_childrens(pid_t *pids, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
}
