/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_utils_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:41:28 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/29 16:04:28 by ielouarr         ###   ########.fr       */
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

int	apply_output_redirection(t_str *files)
{
	int	fd;

	fd = -1;
	if (files->type == APPEND_FILE)
		fd = open(files->s, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(files->s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(files->s);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	apply_input_redirection(t_str *files)
{
	int	fd;

	fd = open(files->s, O_RDONLY);
	if (fd == -1)
	{
		perror(files->s);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
