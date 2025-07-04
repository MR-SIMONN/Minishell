/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:30:54 by moel-hai          #+#    #+#             */
/*   Updated: 2025/07/04 16:54:30 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

int	valid_key(char c)
{
	return (c && c != ' ' && c != '$');
}

int	quotes_len(char *s)
{
	int		i;
	char	c;
	int		flag;
	int		len;

	i = 0;
	len = 0;
	flag = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && !flag)
		{
			c = s[i];
			flag = 1;
		}
		else if (s[i] == c && flag)
		{
			flag = 0;
			len += 2;
		}
		i++;
	}
	return (len);
}

int	is_word(t_token *t)
{
	return (t->type == WORD || is_quoted (t->type)
		|| t->type == VAR || t->type == D_VAR
		|| t->type == S_VAR || t->type == EXPENDED
		|| t->type == EXPORT_ARG || t->type == EX_EXP_ARG);
}

void	split_to_toknes(t_token *curr, t_data *d)
{
	char	**parts;
	t_token	*node;
	t_token	*next;
	int		i;

	parts = ft_split(curr->value, d);
	if (!parts)
		return ;
	curr->value = parts[0];
	curr->type = WORD;
	next = curr->next;
	i = 1;
	while (parts[i])
	{
		node = ft_lstnew(parts[i], d, 0);
		curr->next = node;
		node->next = next;
		curr = node;
		i++;
	}
}
