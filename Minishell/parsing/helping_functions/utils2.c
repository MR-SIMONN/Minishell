/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:10:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/12 04:05:11 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int is_not_redir(t_token_type t)
{
    return (t != REDIRECT_IN
            && t != REDIRECT_OUT
            && t != APPEND
            && t != HEREDOC);
}


void copy_args(char **args, t_token *t, t_data *d)
{
	int i = 0;
	t_token *prev = NULL;

	while (t && t->type != PIPE)
	{
        if ((t->type == WORD || t->next == QUOTED)
        && (!prev || (is_not_redir(prev->type))))
			args[i++] = ft_strdup(t->value, d);
		prev = t;
		t = t->next;
	}
	args[i] = NULL;
}


int args_len(t_token *t)
{
	int len = 0;
	t_token *prev = NULL;

	while (t && t->type != PIPE)
	{
		if ((t->type == WORD || t->next == QUOTED)
        && (!prev || (is_not_redir(prev->type))))
			len++;
		prev = t;
		t = t->next;
	}
	return len;
}
