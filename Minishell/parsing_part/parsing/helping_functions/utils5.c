/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:49:56 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/27 09:28:11 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

int	emty_token(char *s, t_token_type type)
{
	int	i;

	i = 0;
	skip_it(s, &i, ' ');
	if (!s[i] && type == VAR)
		return (1);
	return (0);
}

void	ignore_tokens(t_token **head)
{
	t_token	*curr;
	t_token	*prev;

    curr = *head;
    prev = NULL;
	while (curr)
	{
		if (curr->value && emty_token(curr->value, curr->type))
		{
			if (!prev)
				*head = curr->next;
			else
				prev->next = curr->next;
			curr = curr->next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
int	var_count(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1])
		{
			if (s[i + 1] != '$' && s[i + 1] != ' '
				&& valid_char(s[i + 1]))
				len++;
		}
		i++;
	}
	return (len);
}

int	decrease_len(t_token *t)
{
	int	i;
	int	len;
	int	flag;

	i = 0;
	len = 0;
	flag = 0;
	while (t->value[i])
	{
		if (t->value[i] == '$' && !flag)
		{
			i++;
			while (t->value[i] && valid_char(t->value[i]))
				i++;
			flag = 1;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}
