/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:51 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/25 15:40:22 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int unset_v(t_env **env_lst, t_data *d ,char **args)
{
    int i;
    
    i = 0;
	while(args[i])
    {
        if(ft_strcmp(args[i], "_") == 0)
        {
            i++;
            continue;
        }
        else
        {
            remove_from_env_lst(env_lst, args[i]);
            remove_from_export_lst(&d->exp, args[i]);
        }
        i++;
    }
    return (0);
}