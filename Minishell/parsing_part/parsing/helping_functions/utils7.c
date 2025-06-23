/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 00:46:30 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/23 17:44:50 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

char	*delete_quotes(char *s, char c, int flag, t_data *d)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	len = ft_strlen(s) - quotes_len(s);
	str = ft_malloc(len + 1, d);
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && !flag)
		{
			c = s[i];
			flag = 1;
		}
		else if (s[i] == c && flag)
			flag = 0;
		else
			str[j++] = s[i];
		i++;
	}
	return (str[j] = '\0', str);
}

void	get_rid_of_quotes(t_token *t, t_data *d)
{
	(void)d;
	while (t)
	{
		if (quotes_len(t->value) > 1)
			t->value = delete_quotes(t->value, 0, 0, d);
		t = t->next;
	}
}


