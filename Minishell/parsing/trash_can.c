/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_can.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:52:10 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/18 17:32:27 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(*lst);
		*lst = temp;
	}
}

//this function is to free all the heap allocated memmory throughout the program
void	free_everything(t_data *data)
{
	clear_trash(&data->heap);
	//from now on anything u allocated u must add it to the struct and free it in this function
	
	write(1, "exit\n", 6);
	exit(0);
}