/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:39 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/14 15:00:26 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char	*check_if_env_set(t_env *env_lst, char *env_key)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, env_key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_env_var(t_data *d, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new_node;

	tmp = d->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			tmp->value = ft_strdup(value, d);
			return ;
		}
		tmp = tmp->next;
	}
	printf("allocate new pwd env <<< here\n");
	new_node = ft_malloc(sizeof(t_env), d);
	new_node->key = ft_strdup(key, d);
	new_node->value = ft_strdup(value, d);
	env_add_back(&d->env, new_node);
	printf("success adding .....\n");
	char *pwd = check_if_env_set(d->env, "PWD");
	printf("%s\n", pwd);
}

void	update_env_cd(t_data *d, char *cd_arg)
{
	char	*old_pwd;
	char	new_pwd[1024];

	old_pwd = check_if_env_set(d->env, "PWD");
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories\n", 2);
		update_env_var(d, "PWD", ft_strjoin(check_if_env_set(d->env, "PWD"),
				ft_strjoin("/", cd_arg, d), d));
		return ;
	}
	if (old_pwd)
		update_env_var(d, "OLDPWD", old_pwd);
	update_env_var(d, "PWD", new_pwd);
}

int	cd_v(char **args, t_data *d)
{
	char	*target_path;

	target_path = NULL;
	if (!args[1])
	{
		target_path = check_if_env_set(d->env, "HOME");
		if (!target_path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		target_path = args[1];
	if (chdir(target_path) != 0)
	{
		perror("cd");
		return (1);
	}
	update_env_cd(d, args[1]);
	return (0);
}
