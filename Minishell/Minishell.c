/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:16:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/18 18:04:21 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_str(t_data *data)
{
    int i;

    i = 0;
    
}

void    read_cmds(t_data *data)
{
    char    **lines;

    data->line = readline("\033[1;36m-> minishell\033[0m$");
    if (!data->line)
        free_everything(data);
    store_addr(data->line, data);
    handle_str(data);
}

int main (int ac, char **av, char **env)
{
    t_data  data;

    (void)ac;
    (void)av;
    (void)env;
    while (1 + 1 != 3)
    {
        read_cmds(&data);
    }
}