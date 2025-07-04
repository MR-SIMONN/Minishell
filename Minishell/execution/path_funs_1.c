/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_funs_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:28:10 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/04 16:06:22 by ielouarr         ###   ########.fr       */
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

char	*remove_trailing_slash(char *path, t_data *d)
{
	int		len;
	char	*without_slash;

	if (!path)
		return (NULL);
	len = ft_strlen(path);
	while (len > 0 && path[len - 1] == '/')
		len--;
	without_slash = ft_substr(path, 0, len, d);
	return (without_slash);
}

char	*handle_slash_path(t_cmd *cmds, int *status, t_data *d)
{
	char	*slash_remove;

	if (!is_directory(cmds->cmd))
	{
		slash_remove = remove_trailing_slash(cmds->cmd, d);
		if (access(slash_remove, F_OK) != 0)
		{
			not_found(cmds->cmd);
			*status = 127;
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmds->cmd, 2);
			ft_putstr_fd(": Not a directory\n", 2);
			*status = 126;
		}
	}
	else
	{
		this_is_a_directory(cmds->cmd);
		*status = 126;
	}
	return (NULL);
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
	if (cmds->cmd[0] == '/' || cmds->cmd[0] == '.')
		return (handle_absolute_path(cmds, d, status));
	if (!paths)
		return (handle_no_path(cmds, d, status));
	return (search_in_paths(paths, cmds, d, status));
}
