/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:16:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/23 15:34:02 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int    read_cmds(t_data *d, char **env)
{
    (void)env;
    d->line = readline("\033[1;36m-> minishell\033[0m$");
    if (!d->line)
        return (free_everything(d, 1), 0);
    add_history(d->line);
    store_addr(d->line, d);
    if (parsing(d))
        return (0);
    store_envs(&d->env, env, d);
    expending(d->token, d);
    ignore_tokens(&d->token);
    fill_d_cmd(&d->cmds, d->token, d);
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
        all_good = read_cmds(d, env);
        if (all_good)
        {
            print_tokens(d->token);
            print_cmds(d->cmds);
            // print_envs(d->env);
            execution (d->env, d->cmds, d);
            free_everything(d, -1);
        }
        else
            free_everything(d, -1);
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