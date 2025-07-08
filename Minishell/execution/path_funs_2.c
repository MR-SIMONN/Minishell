/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_funs_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:24:29 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/08 14:25:35 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	**get_path(t_data *d)
{
	t_env	*current;

	current = d->env;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
			break ;
		current = current->next;
	}
	if (!current || !current->value)
		return (NULL);
	return (ft_splits(current->value, ':', d));
}

char	**get_env(t_data *d)
{
	t_env	*current;
	t_env	*saved_current;
	char	**envs;
	int		i;

	current = d->env;
	saved_current = current;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	envs = ft_malloc((i + 1) * sizeof(char *), d);
	i = 0;
	while (saved_current)
	{
		envs[i] = ft_strdup(saved_current->both, d);
		saved_current = saved_current->next;
		i++;
	}
	envs[i] = NULL;
	return (envs);
}

char	*get_fullpath(char *path, char *command, t_data *d)
{
	char	*slash;
	char	*full_path;

	slash = ft_strjoin(path, "/", d);
	full_path = ft_strjoin(slash, command, d);
	return (full_path);
}

int	last_char(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	return (i - 1);
}
