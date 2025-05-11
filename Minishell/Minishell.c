/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:16:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/11 00:45:33 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int    read_cmds(t_data *d)
{
    d->line = readline("\033[1;36m-> minishell\033[0m$");
    if (!d->line)
        return (free_everything(d, 1), 0);
    add_history(d->line);
    store_addr(d->line, d);
    fill_d_cmd(&d->cmds, d->token, d);
    if (parsing(d))
        return (free_everything(d, -1), 0);
    print_cmds(d->cmds);
    return (1);
}

void    minishell(int ac, char **av, char **env, t_data *d)
{
    int all_good;

    all_good = 0;
    (void)ac;
    (void)av;
    (void)env;
    while (1 + 1 == 2)
    {
        set_strcut_values(d);
        all_good = read_cmds(d);
        // print_tokens (d->token);// --> just for testing :)
        if (all_good)
        {
            // execution (d->env, d->cmds, &d);
            free_everything(d, -1);
        }
    }
}

int main (int ac, char **av, char **env)
{
    t_data  data;

    minishell(ac, av, env, &data);
}