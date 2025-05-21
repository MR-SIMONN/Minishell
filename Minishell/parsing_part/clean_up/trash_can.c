/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_can.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:52:10 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/21 16:41:32 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

//this function is to free all the heap allocated memmory that was given to data->heap
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

//this function is to free all the heap allocated memmory throughout the program
void	free_everything(t_data *data, int i)
{
	// printf ("freed\n");// just for debuging
	clear_trash(&data->heap);
	//from now on anything u allocated u must add it to the struct and free it in this function
	//including fds :)
	if (i >= 0)
	{
		printf ("wa exitaaaaaaa %d\n", i);
		exit(i);
	}
}