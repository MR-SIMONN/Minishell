/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:41:57 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/23 01:16:07 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

int	valid_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

t_env	*last_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	env_add_back(t_env **envs, t_env *new)
{
	t_env	*p;

	if (!envs || !new)
		return ;
	if (!*envs)
	{
		*envs = new;
		return ;
	}
	p = last_env(*envs);
	p->next = new;
}

int	is_quoted(t_token_type type)
{
	return (type == D_QUOTED || type == S_QUOTED);
}

void	quotes_stuff(char *s, int i, char *c, int *quotes)
{
	if ((s[i] == '\'' || s[i] == '\"') && !*quotes)
	{
		*c = s[i];
		*quotes = 1;
	}
	else if (s[i] == *c && *quotes)
		*quotes = 0;
}
