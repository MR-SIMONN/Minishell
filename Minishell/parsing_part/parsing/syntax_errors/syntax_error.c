/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:20:24 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/26 23:29:40 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

int	handle_pipes(t_token *t)
{
	while (t && t->next)
	{
		if (!ft_strcmp(t->value, "|") && !ft_strcmp(t->next->value, "|"))
			return (1);
		t = t->next;
	}
	return (0);
}

int	is_rid_nexto_symbol(t_token *t)
{
	if (is_symbol(*t->value) && *t->value != '|')
		if (is_symbol(*t->next->value))
			return (1);
	return (0);
}

int	handle_redirections(t_token *t, t_data *d)
{
	t_token	*p;

	if (!t || !d)
		free_everything(d, 1);
	p = ft_lstlast(t);
	if (is_symbol(*p->value) && !is_quoted(p->type))
		return (1);
	while (t && t->next)
	{
		if (is_rid_nexto_symbol(t))
			return (1);
		t = t->next;
	}
	return (0);
}

int	handle_syntax_error(t_token *t, t_data *d)
{
	int	s_e;

	s_e = 0;
	if (!t)
		free_everything(d, -1);
	s_e = handle_pipes(t);
	if (s_e)
		return (1);
	s_e = handle_redirections(t, d);
	return (s_e);
}
