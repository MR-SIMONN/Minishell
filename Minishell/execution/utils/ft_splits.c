/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:55:43 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/28 22:25:02 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static size_t	count_words(const char *str, char delimiter)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != delimiter
			&& (i == 0 || str[i - 1] == delimiter))
			count++;
		i++;
	}
	return (count);
}

static char	*allocate_words(const char *str, char del, size_t *i, t_data *d)
{
	size_t	start;
	size_t	len;
	char	*word;

	start = *i;
	len = 0;
	while (str[*i] && str[*i] != del)
	{
		(*i)++;
		len++;
	}
	word = ft_malloc((len + 1) * sizeof(char), d);
	if (!word)
		return (NULL);
	len = 0;
	while (start < *i)
	{
		word[len] = str[start];
		len++;
		start++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_splits(char *str, char delimiter, t_data *d)
{
	char	**result;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	result = ft_malloc((count_words(str, delimiter) + 1) * sizeof(char *), d);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != delimiter
			&& (i == 0 || str[i - 1] == delimiter))
		{
			result[j] = allocate_words(str, delimiter, &i, d);
			j++;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}
