/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:09:13 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/02 23:10:20 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static long	nbr_len(int nb)
{
	long	len;

	len = (nb <= 0);
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n, t_data *d)
{
	long	temp;
	long	len;
	char	*str;

	temp = n;
	len = nbr_len (n);
	str = ft_malloc(len + 1, d);
	str[len] = '\0';
	if (temp < 0)
	{
		str[0] = '-';
		temp *= -1;
	}
	if (temp == 0)
		str[0] = '0';
	while (temp)
	{
		str[--len] = (temp % 10) + '0';
		temp /= 10;
	}
	return (str);
}
