/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:39 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/23 17:10:20 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"
// int cd_v(char **args)
// {
//     char *path;

//     if(!args[1])
//         path =  getenv("HOME");
//     else
//         path = args[1];
//     if (!path || chdir(path) != 0)
//     {
//         perror("cd");
//         return (1);
//     }
//     return (0);
// }