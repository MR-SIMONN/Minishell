/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:58:17 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/12 17:16:19 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static char	*check_null(char *s1, char *s2, t_data *d)
{
	if (!s1 && !s2)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2, d));
	if (s2 == NULL)
		return (ft_strdup(s1, d));
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2, t_data *d)
{
	int		i;
	int		j;
	char	*tab;
	int		len;

	if (!s1 || !s2)
		return (check_null(s1, s2, d));
	i = 0;
	j = 0;
	len = ft_strlen (s1) + ft_strlen (s2);
	tab = ft_malloc (len + 1, d);
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}
