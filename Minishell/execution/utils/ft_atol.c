/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:52:51 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/28 22:14:29 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static long	handle_overflow(int sign, unsigned long long n,
				int count, int *range_check)
{
	if (n > (unsigned long long)LLONG_MAX || count > 19)
		*range_check = 1;
	return ((long)(n * sign));
}

long	ft_atol(const char *str, int *range_check)
{
	int					i;
	int					sign;
	unsigned long long	result;
	int					counter;

	i = 0;
	sign = 1;
	result = 0;
	counter = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		counter++;
		i++;
	}
	return (handle_overflow(sign, result, counter, range_check));
}
