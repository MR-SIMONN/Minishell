/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:16:31 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/07 00:50:22 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

t_cmd *new_cmd(t_data *d)
{
    t_cmd *cmd;
    
    cmd = ft_malloc(sizeof(t_cmd), d);
    cmd->args = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->heredoc = 0;
    cmd->heredoc_del = NULL;
    cmd->pipe = 0;
    cmd->next = NULL;
    return cmd;
}

char **add_args(char **argv, t_token *t)
{
    //couns how many words, allocate it
    //n then copy theme one by one
    //n then return it :)
}

void handle_redir(t_token *t, t_cmd *cmd)
{
    if (!t || !t->next)
        return;
    //the paper has it ;)
}

void    fill_d_cmd(t_cmd **c, t_token *t, t_data *d)
{
    t_cmd   *cmd;

    cmd = NULL;
    while (t)
    {
        if (!cmd)
        {
            cmd = new_cmd(d);
            if (!*c)
                *c = cmd;
        }
        if (t->type == WORD && !cmd->args)
            cmd->args = add_args(cmd->args, t);
        else if (t->type == PIPE)
        {
            cmd->pipe = 1;
            ft_cmdadd_back(c, ft_lstcmd(cmd));
            cmd = new_cmd();
        }
        else
            handle_redir(t, cmd);
        t = t->next;
    }
    if (cmd)
        ft_cmdadd_back(c, ft_lstcmd(cmd));//adding the last command u know
}
//handle this wierd cmd ---> cat < in1 >> out1 << EOF > out2