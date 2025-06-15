/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:21:21 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/15 23:58:18 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

int exit_status(int should_update, int new_status)
{
	static int	e;

	if (should_update)
		e = new_status;
	return (e);
}
void    ambiguous_error(char *str)
{
    if (!str)
        return ;
    printf ("minihell: $%s: ambiguous redirect\n", str);
}