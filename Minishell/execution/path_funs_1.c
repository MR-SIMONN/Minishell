/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_funs_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:28:10 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/17 21:31:37 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*search_in_paths(char **paths, t_cmd *cmds, t_data *d, int *status)
{
	int		i;
	char	*full_path;

	i = 0;
	if (cmds->cmd[0] == '\0')
	{
		command_not_found_error(cmds->cmd);
		*status = 127;
		return (NULL);
	}
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

int	path_has_non_directory(char *path, t_data *d)
{
	struct stat	st;
	char		*copy;
	int			i;

	copy = ft_strdup(path, d);
	i = 0;
	while (copy[i])
	{
		if (copy[i] == '/')
		{
			copy[i] = '\0';
			if (copy[0] != '\0')
			{
				if (stat(copy, &st) != 0)
					return (0);
				if (!S_ISDIR(st.st_mode))
					return (1);
			}
			copy[i] = '/';
		}
		i++;
	}
	return (0);
}

char	*handle_absolute_path(t_cmd *cmds, t_data *d, int *status)
{
	struct stat	st;

	if (stat(cmds->cmd, &st) != 0)
	{
		if (path_has_non_directory(cmds->cmd, d))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmds->cmd, 2);
			ft_putstr_fd(": Not a directory\n", 2);
			return ((*status = 126), NULL);
		}
		not_found(cmds->cmd);
		return ((*status = 127), NULL);
	}
	if (S_ISDIR(st.st_mode))
	{
		this_is_a_directory(cmds->cmd);
		return ((*status = 126), NULL);
	}
	if (access(cmds->cmd, X_OK) != 0)
	{
		permission_denied_error(cmds->cmd);
		return ((*status = 126), NULL);
	}
	return (ft_strdup(cmds->cmd, d));
}

char	*handle_slash_path(t_cmd *cmds, int *status, t_data *d)
{
	struct stat	st;

	if (stat(cmds->cmd, &st) != 0)
	{
		if (path_has_non_directory(cmds->cmd, d))
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
		return (NULL);
	if (cmds->cmd && cmds->cmd[0] != '\0'
		&& cmds->cmd[last_char(cmds->cmd)] == '/')
		return (handle_slash_path(cmds, status, d));
	if (ft_strcmp(cmds->cmd, ".") == 0 || ft_strcmp(cmds->cmd, "..") == 0)
	{
		command_not_found_error(cmds->cmd);
		if (ft_strcmp(cmds->cmd, "..") == 0)
			return ((*status = 127), NULL);
		return ((*status = 2), NULL);
	}
	if (slash_char(cmds->cmd))
		return (handle_absolute_path(cmds, d, status));
	if (!paths)
		return (handle_no_path(cmds, d, status));
	return (search_in_paths(paths, cmds, d, status));
}
