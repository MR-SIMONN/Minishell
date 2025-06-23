/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:21:21 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/23 01:32:22 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

int	exit_status(int should_update, int new_status)
{
	static int	e;

	if (should_update)
		e = new_status;
	return (e);
}

void	ambiguous_error(char *str)
{
	if (!str)
		return ;
	printf ("minihell: $%s: ambiguous redirect\n", str);
}

void	quotes_handling(char *s, int *i, int *s_quote, int *d_quote)
{
	if (s[*i] == '\'' && !(*s_quote) && !(*d_quote))
		*s_quote = 1;
	else if (s[*i] == '\'' && *s_quote)
		*s_quote = 0;
	else if (s[*i] == '\"' && !(*s_quote) && !(*d_quote))
		*d_quote = 1;
	else if (s[*i] == '\"' && *d_quote)
		*d_quote = 0;
	(*i)++;
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	ambiguos_detected(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_space(s[i]))
			return (1);
		i++;
	}
	return (0);
}
