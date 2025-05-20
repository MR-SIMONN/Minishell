/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 05:12:07 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/20 07:06:37 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

t_env *new_env(char *s, t_data *d)
{
	t_env *e;

	e = (t_env *)ft_malloc(sizeof(t_env), d);
    e->both = ft_strdup(s, d);
	e->value = copy_envalue(s, d);
	e->key = NULL;
	e->next = NULL;
	return (e);
}

void    store_envs(t_env **envs, char **env, t_data *d)
{
    int i;

    i = 0;
	while (env[i])
	{
		env_add_back(envs, new_env(env[i], d));
		i++;
	}
}