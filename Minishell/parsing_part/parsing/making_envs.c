/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 05:12:07 by moel-hai          #+#    #+#             */
/*   Updated: 2025/07/14 13:36:17 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char	*copy_key(char *s, t_data *d)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	str = ft_substr(s, 0, i, d);
	return (str);
}

char	*copy_envalue(char *s, t_data *d)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	str = ft_substr(s, i + 1, ft_strlen(s) - i - 1, d);
	return (str);
}

t_env	*new_env(char *s, t_data *d)
{
	t_env	*e;

	e = (t_env *)ft_malloc(sizeof(t_env), d);
	e->both = ft_strdup(s, d);
	e->key = copy_key(s, d);
	e->value = copy_envalue(s, d);
	e->next = NULL;
	return (e);
}



void	store_envs(t_env **envs, char **env, t_data *d)
{
	int	i;

	i = 0;
	while (env[i])
	{
		env_add_back(envs, new_env(env[i], d));
		i++;
	}
}
