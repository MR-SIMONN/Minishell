/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:49:56 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/21 15:53:59 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	ignore_tokens(t_token **head)
{
	t_token	*curr;
	t_token	*prev;

    curr = *head;
    prev = NULL;
	while (curr)
	{
		if (curr->value && curr->type == IGNORED)
		{
			if (!prev)
				*head = curr->next; // deleting the head
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
