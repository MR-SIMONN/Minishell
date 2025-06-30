/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:10:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/28 15:11:50 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

int	is_redir(t_token *t)
{
	if (!t)
		return (0);
	return (t->type == REDIRECT_IN
		|| t->type == REDIRECT_OUT
		|| t->type == APPEND
		|| t->type == HEREDOC);
}

void	copy_args(char **args, t_token *t, t_data *d)
{
	int	i;

	if (!t || !d)
		return ;
	i = 0;
	while (t && t->type != PIPE)
	{
		if (is_word(t))
			args[i++] = ft_strdup(t->value, d);
		t = t->next;
	}
	args[i] = NULL;
}

int	args_len(t_token *t)
{
	int	len;

	if (!t)
		return (0);
	len = 0;
	while (t && t->type != PIPE)
	{
		if (is_word(t))
			len++;
		t = t->next;
	}
	return (len);
}

void	after_redir_tokens(t_token *t)
{
	while (t && t->next)
	{
		if (is_redir(t))
		{
			if (t->type != HEREDOC)
			{
				if (t->next->type == WORD || is_quoted(t->next->type))
					t->next->type = REDIR_WORD;
				else if (t->next->type == VAR || t->next->type == S_VAR
					|| t->next->type == D_VAR)
					t->next->type = REDIR_VAR;
			}
			else if (t->type == HEREDOC)
			{
				if (t->next->type == D_VAR || t->next->type == D_QUOTED)
					t->next->type = D_REDIR_WORD;
				else if (t->next->type == S_VAR || t->next->type == S_QUOTED)
					t->next->type = S_REDIR_WORD;
				else if (t->next->type == VAR || t->next->type == WORD)
					t->next->type = REDIR_WORD;
			}
		}
		t = t->next;
	}
}
