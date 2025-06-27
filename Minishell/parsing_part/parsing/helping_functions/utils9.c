/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:51:05 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/27 01:54:23 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

int	D_quoted(char *s)
{
	if (s[0] == '\"' && s[ft_strlen(s) - 1] == '\"')
		return (1);
	return (0);
}

int	is_value_quoted(char *s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '\"' && !quote)
			quote = 1;
		else if (s[i] == '\"' && quote)
			quote = 0;
		else if (s[i] == '=' && s[i + 1] && s[i + 1] == '\"'
				&& !quote)
			return (1);
		i++;
	}
	return (0);
}

int	is_key_quoted(char *s)
{
	int	i;
	int	quote;
	int	before_equale;

	i = 0;
	quote = 0;
	before_equale = 0;
	if (s[0] == '\"')
		quote = 1;
	while (s[i])
	{
		if (s[i] == '\"' && !quote)
			quote = 1;
		if (s[i] == '\"' && quote)
			quote = 0;
		if (s[i] == '\"' && quote && s[i + 1] && s[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}
