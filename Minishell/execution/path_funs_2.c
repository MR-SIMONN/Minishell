/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_funs_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:24:29 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/14 17:52:29 by moel-hai         ###   ########.fr       */
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
	char	**envs;
	int		i;

	i = 0;
	if (!d || !d->env)
		return (NULL);
	current = d->env;
	while (current && ++i)
	{
		current = current->next;
	}
	envs = ft_malloc((i + 1) * sizeof(char *), d);
	current = d->env;
	i = 0;
	while (current)
	{
		if (current->both)
			envs[i] = ft_strdup(current->both, d);
		else
			envs[i] = ft_strdup("", d);
		current = current->next;
		i++;
	}
	return (envs[i] = NULL, envs);
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
