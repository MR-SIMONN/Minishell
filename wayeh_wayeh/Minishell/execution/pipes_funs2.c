/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_funs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:41:14 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/19 20:39:41 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	status_exe_single_external(int pid, int *return_value)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		*return_value = 130;
		ft_putstr_fd("\n", 1);
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		*return_value = 131;
		ft_putstr_fd("Quit: 3\n", 1);
	}
	else
		*return_value = WEXITSTATUS(status);
}

static int	handle_signal_status(int status, int flag)
{
	if (WTERMSIG(status) == SIGINT)
	{
		if (!flag)
			ft_putstr_fd("\n", 1);
		return (130);
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		if (!flag)
			ft_putstr_fd("Quit: 3\n", 1);
		return (131);
	}
	return (1);
}

void	wait_for_children(pid_t *pids, int *final_status, int cmd_count)
{
	int	i;
	int	status;
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
			*final_status = handle_signal_status(status, flag);
			flag = 1;
		}
		else
			*final_status = WEXITSTATUS(status);
		i++;
	}
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
