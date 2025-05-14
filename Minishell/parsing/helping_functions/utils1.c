/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:44:11 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/14 20:03:26 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int empty_cmd(char *s)
{
    int i;

    i = 0;
    skip_it(s, &i, ' ');
	if (s[i] == '|')
		return (syntax_error("syntax error"));
    if (!s[i] || s[i] == ':')
        return (1);
    return (0);
}

t_str	*new_strnode(char *string, t_data *d)
{
	t_str *p;

	p = (t_str *)ft_malloc(sizeof(t_str), d);
	p->s = string;
	p->next = NULL;
	return (p);
}

t_str	*last_str(t_str *p)
{
	if (!p)
		return (NULL);
	while (p->next)
		p = p->next;
	return (p);
}

t_cmd	*last_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_cmdadd_back(t_cmd **c, t_cmd   *new)
{
	t_cmd	*p;

	if (!c || !new)
		return ;
	if (!*c)
	{
		*c = new;
		return ;
	}
	p = last_cmd(*c);
	p->next = new;
}

