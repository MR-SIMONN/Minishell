/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:14:07 by moel-hai          #+#    #+#             */
/*   Updated: 2025/07/05 17:32:46 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

int	syntax_error(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	is_symbol(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	check_one(char *s, int i)
{
	if (!s)
		return (0);
	if (s[i] == '>' || s[i] == '<')
	{
		i++;
		if (is_symbol(s[i]))
			return (1);
	}
	if (s[i] == '|' && s[i + 1])
	{
		if (s[i + 1] == '|')
			return (1);
	}
	return (0);
}

int	check_two(char *s, int i)
{
	if (!s)
		return (0);
	if (s[i] == '>' || s[i] == '<')
	{
		i += 2;
		if (is_symbol(s[i]))
			return (1);
	}
	return (0);
}
