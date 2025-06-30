/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_utils_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 23:22:26 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/30 18:00:48 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_input_fd(int input_fd)
{
	if (input_fd < 0)
	{
		ft_putstr_fd("minishell: invalid input file descriptor\n", 2);
		return (1);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 input");
		return (1);
	}
	close(input_fd);
	return (0);
}

int	ft_output_fd(int output_fd)
{
	if (output_fd < 0)
	{
		ft_putstr_fd("minishell: invalid output file descriptor\n", 2);
		return (1);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output");
		return (1);
	}
	close(output_fd);
	return (0);
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
