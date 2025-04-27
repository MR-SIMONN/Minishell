/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:16:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/27 02:29:54 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void    read_cmds(t_data *d)
{
    int single;
    int dooble;
    
    d->line = readline("\033[1;36m-> minishell\033[0m$");
    if (!d->line)
        free_everything(d, 1);
    store_addr(d->line, d);
    single = quotes_len(d->line, '\'');
    dooble = quotes_len(d->line, '\"');
    if ((single % 2) || (dooble % 2))
        clear_trash(&d->heap);
    ft_lst_tokens (d);
    // handle_syntax_error(d->token);
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
        // free_everything(d, 0);
        clear_trash(&d->heap);
    }
}

int main (int ac, char **av, char **env)
{
    t_data  data;

    parsing(ac, av, env, &data);
}