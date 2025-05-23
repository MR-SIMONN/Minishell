/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:46 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/23 15:26:38 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void    export_v(t_env *list,char **args)
{
    if(!args[1])
    {
        t_env *tmp;
	
	    tmp = list;
	    while(tmp)
	    {
            // ft_putstr_fd("declare -x ", 1);
		    // ft_putstr_fd(tmp->both, 1);
		    // ft_putstr_fd("\n", 1);

            printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		    tmp = tmp->next;
	    }
    }
    // else
    // {
            
    // }
}