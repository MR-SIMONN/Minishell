/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:05:26 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/23 22:53:49 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		i;
	int			flag;

	flag = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			flag = i;
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	if (flag != -1)
		return ((char *)&s[flag]);
	return (NULL);
}
