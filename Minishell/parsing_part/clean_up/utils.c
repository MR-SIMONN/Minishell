/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:31:25 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/28 11:10:46 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	ft_lstadd_front(t_heap **lst, t_heap *p)
{
	if (!p || !lst)
		return ;
	p->next = *lst;
	*lst = p;
}

void	store_addr(char *s, t_data *data)
{
	t_heap	*p;

	if (!s || !data)
		return ;
	p = malloc(sizeof(t_heap));
	if (!p)
	{
		free(s);
		free_everything(data, 1);
	}
	p->address = s;
	p->next = NULL;
	ft_lstadd_front(&data->heap, p);
}

void	*ft_malloc(size_t size, t_data *d)
{
	void	*allocated;
	t_heap	*p;

	if (!d)
		return (NULL);
	p = malloc(sizeof(t_heap));
	if (!p)
	{
		printf ("unexpected error with malloc\n");
		free_everything(d, 1);
	}
	allocated = malloc(size);
	if (!allocated)
	{
		printf ("unexpected error with malloc\n");
		free(p);
		free_everything(d, 1);
	}
	p->address = allocated;
	p->next = NULL;
	ft_lstadd_front(&d->heap, p);
	return (allocated);
}
