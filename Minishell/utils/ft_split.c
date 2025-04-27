/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:02:34 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/26 16:02:34 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static int	ft_cw(char *str, char c)
{
	int		i;
	int		words;
	int		flag;
	char	quote;

	(1) && (i = 0, words = 0, flag = 0, quote = 0);
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (str[i] != c || quote)
		{
			if (flag == 0)
			{
				words++;
				flag = 1;
			}
		}
		else
			flag = 0;
		i++;
	}
	return (words);
}

void	free_all(char **s, int i)
{
	while (i--)
	{
		free (s[i]);
		s[i] = NULL;
	}
	free (s);
	s = NULL;
}

static int	ft_word_len(char *str, int i, char c)
{
	int		word_len;
	char	quote;

	word_len = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (str[i] == c && !quote)
			break ;
		word_len++;
		i++;
	}
	return (word_len);
}

static char	*ft_stridup(char *s, size_t *i, char c)
{
	char	*str;
	int		j;
	int		index;
	char	quote;

	index = *i;
	j = 0;
	quote = 0;
	str = malloc(sizeof(char) * (ft_word_len((char *)s, *i, c) + 1));
	if (!str)
		return (NULL);
	while (s[*i])
	{
		if (!quote && (s[*i] == '\'' || s[*i] == '\"'))
			quote = s[*i];
		else if (quote && s[*i] == quote)
			quote = 0;
		if (s[*i] == c && !quote)
			break ;
		str[j++] = s[*i];
		*i += 1;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_split(char *s, char c, t_data *d)
{
	size_t	i;
	size_t	k;
	char	**str;

	if (!s)
		return (NULL);
	(1) && (i = 0, k = 0, str = malloc (8 * (ft_cw(s, c) + 1)));
	if (!str)
		return (NULL);
	skip_it(s, (int *)&i, c);
	while (s[i])
	{
		if (s[i] != c)
		{
			str[k] = ft_stridup((char *)s, &i, c);
			if (!str[k++])
				return (free_all(str, --k), free_everything(d, 1), NULL);
		}
		skip_it(s, (int *)&i, c);
	}
	return (str[k] = 0, str);
}
