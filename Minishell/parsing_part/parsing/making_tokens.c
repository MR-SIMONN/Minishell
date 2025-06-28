/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:34:46 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/28 12:57:14 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	make_tokens(char **t, t_token **p, t_data *d)
{
	int	i;
	int	quote;

	i = 0;
	while (t[i])
	{
		quote = 0;
		if (t[i][0] == '\'' || t[i][0] == '\"' || quotes_len(t[i]) > 1)
		{
			if (t[i][0] == '\'')
				quote = 1;
			else if (t[i][0] == '\"')
				quote = 2;
		}
		ft_lstadd_back(p, ft_lstnew(t[i], d, quote));
		i++;
	}
}

void	spaces_len(char *s, int *i, int *len, int quote)
{
	if (is_two_symbols(s, *i))
	{
		if (!quote)
			handle_symbols(s, len, *i);
		*len += 2;
		(*i)++;
	}
	else if (is_one_symbol(s, *i))
	{
		if (!quote)
		{
			if (*i > 0 && s[*i - 1] != ' ')
				(*len)++;
			if (s[*i + 1] && s[*i + 1] != ' ')
				(*len)++;
		}
		(*len)++;
	}
	else
		(*len)++;
}

int	extra_strlen(char *s)
{
	int		i;
	int		len;
	int		quote;
	char	c;

	i = 0;
	len = 0;
	quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && !quote)
		{
			c = s[i];
			quote = 1;
		}
		else if (s[i] == c && quote)
			quote = 0;
		spaces_len(s, &i, &len, quote);
		i++;
	}
	return (len);
}

void	ft_lst_tokens(t_data *d)
{
	int		len;
	char	*str;
	char	**tokens;

	len = extra_strlen(d->line);
	str = ft_strsdup(d->line, len, d);
	tokens = ft_split(str, d);
	make_tokens(tokens, &d->token, d);
}
