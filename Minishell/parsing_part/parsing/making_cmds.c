/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:16:31 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/23 00:37:34 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	stradd_back(t_str **h, t_str *new)
{
	t_str	*p;

	if (!h || !new)
		return ;
	if (!*h)
	{
		*h = new;
		return ;
	}
	p = last_str(*h);
	p->next = new;
}

t_cmd	*new_cmd(t_data *d)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd), d);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->files = NULL;
	cmd->heredoc = 0;
	cmd->heredoc_del = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	return (cmd);
}

char	**add_args(t_token *t, t_data *d)
{
	int		len;
	char	**args;

	len = args_len(t);
	args = ft_malloc(sizeof(char *) * (len + 1), d);
	if (t)
		copy_args(args, t, d);
	return (args);
}

void	handle_redir(t_token *t, t_cmd *cmd, t_data *d)
{
	char	*n_t;

	if (!t || !t->next || !t->next->value)
		return ;
	n_t = t->next->value;
	if (t->type == HEREDOC)
	{
		stradd_back(&cmd->heredoc_del, new_strnode(ft_strdup(n_t, d), t, d));
		cmd->heredoc = 1;
	}
	else if (t->type == REDIRECT_IN || t->type == REDIRECT_OUT
		|| t->type == APPEND)
		stradd_back(&cmd->files, new_strnode(ft_strdup(n_t, d), t, d));
}

void	fill_d_cmd(t_cmd **c, t_token *t, t_data *d)
{
	t_cmd	*cmd;

	cmd = NULL;
	while (t)
	{
		if (!cmd)
			cmd = new_cmd(d);
		if (is_word(t) && !cmd->args)
		{
			cmd->args = add_args(t, d);
			if (cmd->args && cmd->args[0])
				cmd->cmd = ft_strdup(cmd->args[0], d);
		}
		if (t->type != WORD && t->type != PIPE && !is_quoted (t->type))
			handle_redir(t, cmd, d);
		if (t->type == PIPE)
		{
			cmd->pipe = 1;
			ft_cmdadd_back(c, cmd);
			cmd = NULL;
		}
		t = t->next;
	}
	if (cmd)
		ft_cmdadd_back(c, cmd);
}
