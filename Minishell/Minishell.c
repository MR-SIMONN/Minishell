/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:16:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/07/16 20:33:21 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (sig_check(0, 0))
	{
		write (1, "\n", 1);
		return ;
	}
	exit_status(1, 1);
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_stuff(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	read_cmds(t_data *d)
{
	d->line = readline("-> minishell$ ");
	if (!d->line)
	{
		ft_putstr_fd("exit\n", 1);
		free_everything(d, exit_status(0, 0));
	}
	if (d->line[0])
		add_history(d->line);
	store_addr(d->line, d);
	if (parsing(d))
		return (0);
	if (expending(d->token, d, 0, 0))
		return (0);
	ignore_tokens(&d->token);
	get_rid_of_quotes(d->token, d);
	fill_d_cmd(&d->cmds, d->token, d);
	if (exceeded_heredocs(d->cmds))
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		free_everything(d, 2);
	}
	return (1);
}

void	minishell(int ac, char **av, char **env, t_data *d)
{
	int	all_good;

	all_good = 0;
	(void)ac;
	(void)av;
	set_strcut_values(d, 0);
	store_envs(&d->env, env, d);
	d->backup_pwd = var_value(d->env, "PWD", d);
	signal_stuff();
	rl_catch_signals = 0;
	while (1 + 1 == 2)
	{
		set_strcut_values(d, 1);
		all_good = read_cmds(d);
		if (all_good)
		{
			sig_check(1, 1);
			exit_status(1, 0);
			execution(d);
			sig_check(1, 0);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (!isatty(0) || !isatty(1))
		return (1);
	minishell(ac, av, env, &data);
}
