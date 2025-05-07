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

void    cmd_n_args_init(t_cmd *cmd, t_token *t, t_data *d)
{
    while (t)
    {
        if (t->type == PIPE)
        {
            
        }
        t = t->next;
    }
}

void    fill_d_cmd(t_cmd *cmd, t_token *t, t_data *d)
{
    int len;
    char *str;
    char **tokens;
    
    len = extra_strlen(d->line);
    str = ft_strsdup(d->line, len, d);

    cmd_n_args_init(cmd, t, d);
    tokens = ft_split(str, ' ', d);
    if (!tokens)
        free_everything(d, 1);
    make_tokens(tokens, &d->token, d);
}
//handle this wierd cmd ---> cat < in1 >> out1 << EOF > out2