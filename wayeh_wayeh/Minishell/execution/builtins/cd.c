/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:39 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/16 20:35:22 by moel-hai         ###   ########.fr       */
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

int	check_if_env(t_env *env_lst, char *env_key)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, env_key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	update_env_cd(t_data *d, char *cd_arg)
{
	char	*old_pwd;
	char	*new_pwd;

	if (check_if_env(d->env, "PWD"))
		old_pwd = check_if_env_set(d->env, "PWD");
	new_pwd = getcwd(NULL, 0);
	store_addr(new_pwd, d);
	if (!new_pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories\n", 2);
		d->backup_pwd = ft_strjoin(d->backup_pwd,
				ft_strjoin("/", cd_arg, d), d);
		add_or_update_env(d, "PWD", ft_strdup(d->backup_pwd, d));
		return ;
	}
	if (old_pwd)
		add_or_update_env(d, "OLDPWD", old_pwd);
	add_or_update_env(d, "PWD", new_pwd);
	d->backup_pwd = var_value(d->env, "PWD", d);
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
	if (target_path[0] == '\0')
		target_path = ".";
	if (chdir(target_path) != 0)
	{
		perror("cd");
		return (1);
	}
	update_env_cd(d, args[1]);
	return (0);
}
