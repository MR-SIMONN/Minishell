/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_funs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:41:14 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/16 20:34:30 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static int	handle_signal_status(int status, int flag)
{
	if (WTERMSIG(status) == SIGINT)
		return (130);
	else if (WTERMSIG(status) == SIGQUIT)
	{
		if (!flag)
			ft_putstr_fd("Quit: 3", 1);
		return (131);
	}
	return (1);
}

int	wait_for_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	final_status;
	int	flag;

	flag = 0;
	i = 0;
	while (i < cmd_count)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pids[i], &status, 0);
		signal(SIGINT, handle_sigint);
		if (WIFSIGNALED(status))
		{
			final_status = handle_signal_status(status, flag);
			if (!flag)
				ft_putstr_fd("\n", 1);
			flag = 1;
		}
		else
			final_status = WEXITSTATUS(status);
		i++;
	}
	return (final_status);
}

void	wait_children(pid_t *pids, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		kill(pids[j], SIGKILL);
		waitpid(pids[j], NULL, 0);
		j++;
	}
}
