/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:43:38 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/24 15:59:51 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

t_env	*ft_lstnew_export_to_env(char *key, char *value, char *both, t_data *d)
{
	t_env	*allocate;

	allocate = ft_malloc(sizeof(t_env), d);
	allocate->key=key;
    allocate->value=value;
    allocate->both=both;
	allocate->next = NULL;
	return (allocate);
}
t_exp	*ft_lstnew_export_to_value(char *value, t_data *d)
{
	t_exp	*allocate;

	allocate = ft_malloc(sizeof(t_exp), d);
    allocate->value=value;
	allocate->next = NULL;
	return (allocate);
}