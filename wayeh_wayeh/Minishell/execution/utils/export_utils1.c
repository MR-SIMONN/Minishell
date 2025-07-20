/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:46:57 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/16 12:55:44 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	update_env_value(t_env *node, char *new_value, char *new_both)
{
	if (!node)
		return ;
	node->value = new_value;
	node->both = new_both;
}

void	handle_export_only(char *arg, t_data *d)
{
	char	*key;
	t_exp	*new_exp;

	key = ft_strdup(arg, d);
	if (!is_exported(d->exp, d->env, key))
	{
		new_exp = ft_lstnew_export_to_value(key, d);
		ft_exp_lstadd_back(&d->exp, new_exp);
	}
}

void	export_displayer(t_env *env_lst, t_exp *exp_lst)
{
	while (env_lst)
	{
		if (env_lst->key && env_lst->value)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env_lst->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env_lst->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		env_lst = env_lst->next;
	}
	while (exp_lst)
	{
		if (exp_lst->value)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(exp_lst->value, 1);
			ft_putstr_fd("\n", 1);
		}
		exp_lst = exp_lst->next;
	}
}

int	is_valid_identifier(char *str, int len)
{
	int	i;

	if (len == 0)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (i < len)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
