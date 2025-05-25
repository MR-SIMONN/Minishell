/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:46 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/25 15:37:58 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static void	export_displayer(t_env *env_lst, t_exp *exp_lst)
{
	t_env	*tmp;
	t_exp	*tmp1;

	tmp = env_lst;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	tmp1 = exp_lst;
	while (tmp1)
	{
		printf("declare -x %s\n", tmp1->value);
		tmp1 = tmp1->next;
	}
}

static int	is_valid_identifier(char *str, int len)
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

static void	update_env_value(t_env *node, char *new_value, char *new_both)
{
	if (!node)
		return ;
	node->value = new_value;
	node->both = new_both;
}


static void	handle_append(t_env **env_lst, char *arg, t_data *d)
{
	int		plus_pos;
	char	*key;
	char	*append_value;
	t_env	*existing;
	t_exp	*export_existing;
	char	*new_value;
	char	*both;
	t_env	*new_node;

	plus_pos = 0;
	while (!(arg[plus_pos] == '+' && arg[plus_pos + 1] == '='))
		plus_pos++;
	key = ft_substr(arg, 0, plus_pos, d);
	append_value = ft_substr(arg, plus_pos + 2, 
			ft_strlen(arg) - plus_pos - 2, d);
	existing = find_env_node(*env_lst, key);
	export_existing = find_exp_node(d->exp, key);
	if (existing)
	{
		new_value = ft_strjoin(existing->value, append_value, d);
		both = ft_strjoin_eq(key, new_value, d);
		update_env_value(existing, new_value, both);
	}
	else
	{
		if(export_existing)
			remove_from_export_lst(&d->exp, key);
		both = ft_strjoin_eq(key, append_value, d);
		new_node = ft_lstnew_export_to_env(key, append_value, both, d);
		ft_env_lstadd_back(env_lst, new_node);
		
	}
}

static void	handle_assignment(t_env **env_lst, char *arg, t_data *d)
{
	int		eq_pos;
	char	*key;
	char	*value;
	char	*both;
	t_env	*existing;
	t_exp	*export_existing;
	t_env	*new_node;

	eq_pos = 0;
	while (arg[eq_pos] != '=')
		eq_pos++;
	key = ft_substr(arg, 0, eq_pos, d);
	value = ft_substr(arg, eq_pos + 1, ft_strlen(arg) - eq_pos - 1, d);
	both = ft_strjoin_eq(key, value, d);
	existing = find_env_node(*env_lst, key);
	export_existing = find_exp_node(d->exp, key);
	if (existing)
	{
		update_env_value(existing, value, both);
	}
	else
	{
		if(export_existing)
			remove_from_export_lst(&d->exp, key);
		new_node = ft_lstnew_export_to_env(key, value, both, d);
		ft_env_lstadd_back(env_lst, new_node);
	}
}

static void	handle_export_only(char *arg, t_data *d)
{
	char	*key;
	t_exp	*new_exp;

	key = ft_strdup(arg, d);
	if (!is_exported(d->exp, key))
	{
		new_exp = ft_lstnew_export_to_value(key, d);
		ft_exp_lstadd_back(&d->exp, new_exp);
	}
}

int	export_v(t_env **env_lst, char **args, t_data *d)
{
	int		i;
	char	*arg;
	int		j;

	i = 1;
	if (!args[1])
	{
		export_displayer(*env_lst, d->exp);
		return (0);
	}
	while (args[i])
	{
		arg = args[i];
		j = 0;
		while (arg[j] && arg[j] != '=' && !(arg[j] == '+' && arg[j + 1] == '='))
			j++;
		if (!is_valid_identifier(arg, j) || arg[0] == '=')
		{
			printf("export: `%s`: not a valid identifier\n", arg);
			i++;
			continue ;
		}
		if (ft_strnstr(arg, "+=", ft_strlen(arg)))
			handle_append(env_lst, arg, d);
		else if (ft_strchr(arg, '='))
			handle_assignment(env_lst, arg, d);
		else
			handle_export_only(arg, d);
		i++;
	}
	return (0);
}