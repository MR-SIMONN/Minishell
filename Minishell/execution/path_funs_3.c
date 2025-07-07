/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_funs_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:34:06 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/07 09:27:44 by ielouarr         ###   ########.fr       */
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

int	is_exec(char *path, t_cmd *cmds, int silent, int *status)
{
	if (is_directory(path))
	{
		if (!silent)
			this_is_a_directory(cmds->cmd);
		*status = 126;
		return (126);
	}
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
