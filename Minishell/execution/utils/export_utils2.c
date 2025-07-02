/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:32:49 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/29 15:54:32 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	append_to_existing_env(t_env *existing, char *key,
				char *append_value, t_data *d)
{
	char	*new_value;
	char	*both;

	new_value = ft_strjoin(existing->value, append_value, d);
	both = ft_strjoin_eq(key, new_value, d);
	update_env_value(existing, new_value, both);
}

void	create_new_env_node(t_data *d, char *key, char *value)
{
	t_exp	*export_existing;
	t_env	*new_node;
	char	*both;

	export_existing = find_exp_node(d->exp, key);
	if (export_existing)
		remove_from_export_lst(&d->exp, key);
	both = ft_strjoin_eq(key, value, d);
	new_node = ft_lstnew_export_to_env(key, value, both, d);
	ft_env_lstadd_back(&d->env, new_node);
}

void	add_or_update_env(t_data *d, char *key, char *value)
{
	t_env	*existing;
	char	*both;

	existing = find_env_node(d->env, key);
	if (existing)
	{
		both = ft_strjoin_eq(key, value, d);
		update_env_value(existing, value, both);
	}
	else
		create_new_env_node(d, key, value);
}
