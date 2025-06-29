/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:16:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/29 10:56:18 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int gv_sig ;

void	handle_sigint(int sig)
{
	if (gv_sig == 1)
	{
		printf("\n");
		return;
	}
	(void)sig;
	exit_status(1, 1);
	printf ("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_stuff(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int    read_cmds(t_data *d)
{
    d->line = readline("-> minishell$ ");
    if (!d->line)
        return (free_everything(d, 1), 0);
    add_history(d->line);
    store_addr(d->line, d);
    if (parsing(d))
        return (0);
    if (expending(d->token, d, 0, 0))
        return (0);
    ignore_tokens(&d->token);
    get_rid_of_quotes(d->token, d);
    fill_d_cmd(&d->cmds, d->token, d);
    return (1);
}

void    minishell(int ac, char **av, char **env, t_data *d)
{
    int all_good;
 
    all_good = 0;
    gv_sig = 0;
    (void)ac;
    (void)av;
    set_strcut_values(d, 0);
    store_envs(&d->env, env, d);
    signal_stuff();
    rl_catch_signals = 0;
    while (1 + 1 == 2)
    {
        set_strcut_values(d, 1);
        all_good = read_cmds(d);
        if (all_good)
        {
            exit_status(0, 1);
            // print_tokens(d->token);
            // print_cmds(d->cmds);
            // print_envs(d->env);
            gv_sig = 1;
			exit_status(1, 0);
            execution (d);
            gv_sig = 0;
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

    if (!isatty(0) || !isatty(1))
        return (1);
    // atexit(ff);
    minishell(ac, av, env, &data);
    
}