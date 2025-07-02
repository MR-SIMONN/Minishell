/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:41:28 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/02 14:29:20 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	apply_redirections(t_str *files, t_cmd *cmd)
{
	while (files)
	{
		if(files->type == HERDOC_DEL && apply_heredoc_redirection(cmd) != 0)
			return(1);
		if ((files->type == APPEND_FILE || files->type == OUT_FILE)
			&& apply_output_redirection(files) != 0)
			return (1);
		if (files->type == IN_FILE && apply_input_redirection(files) != 0)
			return (1);
		files = files->next;
	}
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


