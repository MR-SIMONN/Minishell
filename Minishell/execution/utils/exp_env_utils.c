/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:54:02 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/30 23:31:26 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	is_exported(t_exp *exp_lst, t_env *env_lst, char *key)
{
	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
			return (1);
		env_lst = env_lst->next;
	}
	while (exp_lst)
	{
		if (ft_strcmp(exp_lst->value, key) == 0)
			return (1);
		exp_lst = exp_lst->next;
	}
	return (0);
}

t_env	*find_env_node(t_env *env_lst, char *key)
{
	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

t_exp	*find_exp_node(t_exp *exp_lst, char *key)
{
	while (exp_lst)
	{
		if (ft_strcmp(exp_lst->value, key) == 0)
			return (exp_lst);
		exp_lst = exp_lst->next;
	}
	return (NULL);
}

void	remove_from_export_lst(t_exp **exp_lst, char *key)
{
	t_exp	*curr_tmp;
	t_exp	*pre_tmp;

	curr_tmp = *exp_lst;
	pre_tmp = NULL;
	while (curr_tmp)
	{
		if (ft_strcmp(curr_tmp->value, key) == 0)
		{
			if (!pre_tmp)
				*exp_lst = curr_tmp->next;
			else
				pre_tmp->next = curr_tmp->next;
			return ;
		}
		pre_tmp = curr_tmp;
		curr_tmp = curr_tmp->next;
	}
}

void	remove_from_env_lst(t_env **env_lst, char *key)
{
	t_env	*curr_tmp;
	t_env	*pre_tmp;

	curr_tmp = *env_lst;
	pre_tmp = NULL;
	while (curr_tmp)
	{
		if (ft_strcmp(curr_tmp->key, key) == 0)
		{
			if (!pre_tmp)
				*env_lst = curr_tmp->next;
			else
				pre_tmp->next = curr_tmp->next;
			return ;
		}
		pre_tmp = curr_tmp;
		curr_tmp = curr_tmp->next;
	}
}
