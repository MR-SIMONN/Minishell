/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:02:27 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/26 16:02:27 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int is_variable(char *s, int quote)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '$' && s[i + 1])
        {
            if (quote == 0)
                return (0);
            else if (quote == 1)
                return (1);
            else
                return (2);
        }
        i++;
    }
    return (-1);
}

t_token_type    token_type(char *s, int quote)
{
    if (is_variable(s, quote) == 0)
        return (VAR);
    else if (is_variable(s, quote) == 1)
        return (S_VAR);
    else if (is_variable(s, quote) == 2)
        return (D_VAR);
    else if (quote == 1)
        return (S_QUOTED);
    else if (quote == 2)
        return (D_QUOTED);
    else if (is_one_symbol(s, 0))
    {
        if (s[0] == '|')
            return (PIPE);
        else if (s[0] == '>')
            return (REDIRECT_OUT);
        else if (s[0] == '<')
            return (REDIRECT_IN);
    }
    else if (is_two_symbols(s, 0))
    {
        if (s[0] == '>')
            return (APPEND);
        else if (s[0] == '<')
            return (HEREDOC);
    }
    return (WORD);
}

t_token *ft_lstnew(char *content, t_data *d, int quote)
{
	t_token *s;

	s = (t_token *)ft_malloc(sizeof(t_token), d);
	s->value = content;
	s->type = token_type(content, quote);
	s->next = NULL;
	return (s);
}
