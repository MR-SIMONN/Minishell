/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_funs_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:28:10 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/07 09:34:48 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*search_in_paths(char **paths, t_cmd *cmds, t_data *d, int *status)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = get_fullpath(paths[i], cmds->cmd, d);
		if (is_exec(full_path, cmds, 1, status) == 0)
			return (full_path);
		i++;
	}
	command_not_found_error(cmds->cmd);
	*status = 127;
	return (NULL);
}

int	handle_directory_path(char *path, t_cmd *cmds, int silent, int *status)
{
	if (is_directory(path))
	{
		if (!silent)
			this_is_a_directory(cmds->cmd);
		*status = 126;
		return (126);
	}
	if (!silent)
		not_found(path);
	*status = 127;
	return (127);
}

char	*handle_slash_path(t_cmd *cmds, int *status, t_data *d)
{
	struct stat	st;
	char		*clean;

	clean = remove_trailing_slash(cmds->cmd, d);
	if (stat(clean, &st) != 0)
	{
		if (path_has_non_directory(clean, d))
		{
			not_a_directory(cmds->cmd);
			*status = 126;
		}
		else
		{
			not_found(cmds->cmd);
			*status = 127;
		}
		return (NULL);
	}
	if (S_ISDIR(st.st_mode))
	{
		this_is_a_directory(cmds->cmd);
		return ((*status = 126), NULL);
	}
	not_a_directory(cmds->cmd);
	return ((*status = 126), NULL);
}

char	*right_path(char **paths, t_cmd *cmds, t_data *d, int *status)
{
	if (!cmds->cmd)
	{
		*status = 127;
		return (NULL);
	}
	if (cmds->cmd && cmds->cmd[0] != '\0'
		&& cmds->cmd[last_char(cmds->cmd)] == '/')
		return (handle_slash_path(cmds, status, d));
	if (slash_char(cmds->cmd))
		return (handle_absolute_path(cmds, d, status));
	if (!paths)
		return (handle_no_path(cmds, d, status));
	return (search_in_paths(paths, cmds, d, status));
}
