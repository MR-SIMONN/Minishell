/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:16:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/26 19:26:29 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


void    read_cmds(t_data *d)
{
    d->line = readline("\033[1;36m-> minishell\033[0m$");
    if (!d->line)
        free_everything(d);
    store_addr(d->line, d);
    ft_lst_tokens (d);
}
    
int main (int ac, char **av, char **env)
{
    t_data  data;

    (void)ac;
    (void)av;
    (void)env;
    while (1 + 1 == 2)
    {
        set_strcut_values(&data);
        read_cmds(&data);
        print_tokens (data.token);
        free_everything(&data);
    }
}