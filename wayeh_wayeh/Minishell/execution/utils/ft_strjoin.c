/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:03:54 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/28 22:12:35 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char	*ft_strjoin_eq(char *s1, char *s2, t_data *d)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	res = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 2, d);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = '=';
	while (s2[j])
	{
		res[i++] = s2[j++];
	}
	res[i] = '\0';
	return (res);
}
