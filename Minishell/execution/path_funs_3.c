/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_funs_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:34:06 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/08 15:41:28 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*handle_no_path(t_cmd *cmds, t_data *d, int *status)
{
	struct stat	st;

	if (stat(cmds->cmd, &st) != 0)
	{
		command_not_found_error(cmds->cmd);
		*status = 127;
		return (NULL);
	}
	if (S_ISDIR(st.st_mode))
	{
		this_is_a_directory(cmds->cmd);
		*status = 126;
		return (NULL);
	}
	if (access(cmds->cmd, X_OK) != 0)
	{
		permission_denied_error(cmds->cmd);
		*status = 126;
		return (NULL);
	}
	return (ft_strdup(cmds->cmd, d));
}

int	is_exec(char *path, t_cmd *cmds, int silent, int *status)
{
	if (access(path, F_OK) != 0)
	{
		if (!silent)
			command_not_found_error(cmds->cmd);
		*status = 127;
		return (127);
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
