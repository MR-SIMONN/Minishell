/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:16:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/16 15:28:32 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int    read_cmds(t_data *d)
{
    d->line = readline("-> minishell$ ");
    if (!d->line)
        return (free_everything(d, 1), 0);
    add_history(d->line);
    store_addr(d->line, d);
    if (parsing(d))
        return (0);
    expending(d->token, d, 0);
    ignore_tokens(&d->token);
    get_rid_of_quotes(d->token, d);
    fill_d_cmd(&d->cmds, d->token, d);
    return (1);
}

void    minishell(int ac, char **av, char **env, t_data *d)
{
    int all_good;
 
    all_good = 0;
    (void)ac;
    (void)av;
    set_strcut_values(d, 0);
    store_envs(&d->env, env, d);
    while (1 + 1 == 2)
    {
        set_strcut_values(d, 1);
        all_good = read_cmds(d);
        if (all_good)
        {
            d->exit_value = 0;
            // print_tokens(d->token);
            // print_cmds(d->cmds);
            // print_envs(d->env);
            execution (&d->env, d->cmds, d);
        }
    }
}

// void ff()
// {
//     system("leaks Minishell");
// }

int main (int ac, char **av, char **env)
{
    t_data  data;

    // atexit(ff);
    minishell(ac, av, env, &data);
    
}