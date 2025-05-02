/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:16:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/02 01:03:40 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void    read_cmds(t_data *d)
{
    d->line = readline("\033[1;36m-> minishell\033[0m$");
    if (!d->line)
        free_everything(d, 1);
    add_history(d->line);
    store_addr(d->line, d);
    if (empty_cmd(d->line))
        free_everything(d, 0);
    is_invalid_syntax(d->line, d);
    ft_lst_tokens (d);
    handle_syntax_error(d->token, d);
}

void    parsing(int ac, char **av, char **env, t_data *d)
{
    (void)ac;
    (void)av;
    (void)env;
    while (1 + 1 == 2)
    {
        set_strcut_values(d);
        read_cmds(d);
        print_tokens (d->token);// --> just for testing :)
        free_everything(d, -1);
        // clear_trash(&d->heap);
    }
}

int main (int ac, char **av, char **env)
{
    t_data  data;

    parsing(ac, av, env, &data);
    // execution (env, data->cmds, &data);
}