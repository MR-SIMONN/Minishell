/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_funs_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:34:06 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/02 18:04:46 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*handle_absolute_path(t_cmd *cmds, t_data *d, int *status)
{
	if (is_exec(cmds->cmd, cmds, 0, status) == 0)
		return (ft_strdup(cmds->cmd, d));
	return (NULL);
}

int	is_exec(char *path, t_cmd *cmds, int silent, int *status)
{
	if (path[last_char(path)] == '/')
		return (handle_directory_path(path, cmds, silent, status));
	if (access(path, F_OK) != 0)
	{
		if (!silent)
			command_not_found_error(cmds->cmd);
		*status = 127;
		return (127);
	}
	if (is_directory(path))
	{
		if (!silent)
			this_is_a_directory(cmds->cmd);
		*status = 126;
		return (126);
	}
	if (access(path, X_OK) != 0)
	{
		if (!silent)
			permission_denied_error(path);
		*status = 126;
		return (126);
	}
	return (0);
}
