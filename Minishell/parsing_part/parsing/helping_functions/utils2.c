/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:10:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/24 16:56:22 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

int is_not_redir(t_token *t)
{
	if (!t)
		return (1);
	if (t->type != REDIRECT_IN
            && t->type != REDIRECT_OUT
            && t->type != APPEND
            && t->type != HEREDOC)
		{
			return (1);
		}
	return (0);
}

void copy_args(char **args, t_token *t, t_data *d)
{
	int 	i;

	i = 0;
	while (t && t->type != PIPE)
	{
        if ((t->type == WORD || is_quoted (t->type)
			|| t->type == VAR))
			args[i++] = ft_strdup(t->value, d);
		t = t->next;
	}
	args[i] = NULL;
}


int args_len(t_token *t)
{
	int 	len;

	len = 0;
	while (t && t->type != PIPE)
	{
        if ((t->type == WORD || is_quoted (t->type)
			|| t->type == VAR))
			len++;
		t = t->next;
	}
	return (len);
}

int	no_pipeout(char *s, int i)
{
	if (i > 0 && s[i] == '|' && s[i - 1] == '>')
		return (0);
	return (1);
}
void	change_tokens_types(t_token *t)
{
	while (t && t->next)
	{
		if (!is_not_redir(t))
		{
			if (t->next->type == WORD)
				t->next->type = REDIR_WORD;
		}
		t = t->next;
	}
}
