/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:44:11 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/27 22:49:19 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int empty_cmd(char *s)
{
    int i;

    i = 0;
    skip_it(s, &i, ' ');
    if (!s[i])
        return (1);
    return (0);
}

t_cmd	*ft_lstlast(t_cmd *lst)
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
	p = ft_lstlast(*c);
	p->next = new;
}