/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:30:54 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/05 00:41:01 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

void	make_backup_env(t_env **envs, t_data *d)
{
	char	*pwd;

    pwd = NULL;
	if (getcwd(pwd, 1024))
		env_add_back(envs, new_env(ft_strjoin("PWD=", pwd, d), d));
	else
		env_add_back(envs, new_env("PWD=/", d));
	env_add_back(envs, new_env("SHLVL=1", d));
	env_add_back(envs, new_env(ft_strjoin("_=", ft_strjoin(pwd, "/Minishell", d), d), d));
	env_add_back(envs, new_env(ft_strjoin("PATH=", THE_PATH, d), d));
}
int valid_key(char c)
{
	return (c && c != ' ' && c != '$');
}

int quotes_len (char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			len++;
		i++;
	}
	return (len);
}

int is_word(t_token *t)
{
	return ((t->type == WORD || is_quoted (t->type)
			|| t->type == VAR || t->type == D_VAR));
}