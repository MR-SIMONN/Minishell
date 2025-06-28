/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_can.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:52:10 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/28 10:49:26 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	clear_trash(t_heap **lst)
{
	t_heap	*temp;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->address);
		(*lst)->address = NULL;
		free(*lst);
		*lst = temp;
	}
}

void	free_everything(t_data *data, int i)
{
	clear_trash(&data->heap);
	if (i >= 0)
	{
		printf ("exit");
		exit(i);
	}
}
