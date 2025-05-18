/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:30:32 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/18 17:18:03 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len, t_data *d)
{
	size_t			i;
	char			*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen (s))
	{
		str = ft_malloc (1, d);
		return (*str = '\0', str);
	}
	if (len > ft_strlen (s + start))
		len = ft_strlen (s + start);
	i = 0;
	str = ft_malloc (len + 1, d);
	while (i < len)
		str[i++] = s[start++];
	return (str[i] = '\0', str);
}
