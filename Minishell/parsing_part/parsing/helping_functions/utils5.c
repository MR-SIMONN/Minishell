/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:49:56 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/14 14:18:04 by ielouarr         ###   ########.fr       */
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
		if (s[i] == '$' && is_var(s[i + 1]))
				len++;
		i++;
	}
	return (len);
}

int	decrease_len(char *s)
{
	int	i;
	int	len;
	int	flag;

	i = 0;
	len = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == '$' && !flag)
		{
			i++;
			while (s[i] && valid_char(s[i]))
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

int	is_var(char c)
{
	return (c && (valid_char(c) || c == '?'));
}