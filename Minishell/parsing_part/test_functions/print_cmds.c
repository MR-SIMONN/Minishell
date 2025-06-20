/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 05:38:47 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/20 17:57:30 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static const char *redir_type_str(t_redir_type type)
{
    if (type == OUT_FILE)
        return "OUT_FILE";
    if (type == IN_FILE)
        return "IN_FILE";
    if (type == APPEND_FILE)
        return "APPEND_FILE";
    if (type == HERDOC_DEL)
        return "HERDOC_DEL";
    return "UNKNOWN";
}

// print combined files list with types
void print_files_list(t_str *lst)
{
    printf("Files:\n");
    if (!lst)
    {
        printf("  (none)\n");
        return;
    }
    while (lst)
    {
        printf("  [%s: %s]\n", redir_type_str(lst->type), lst->s);
        lst = lst->next;
    }
}

// print string linked list with a label
static void print_str_list(t_str *lst, const char *label)
{
    printf("%s:\n", label);
    if (!lst)
    {
        printf("  (none)\n");
        return;
    }
    while (lst)
    {
        printf("  %s\n", lst->s);
        lst = lst->next;
    }
}

void print_cmds(t_cmd *cmd)
{
    int i;

    printf("\n---  cmd list  -------------------------------------------------------\n");
    while (cmd)
    {
        printf("---- CMD ----\n");
        if (cmd->cmd)
            printf("Cmd: %s\n", cmd->cmd);
        else
            printf("Cmd: (null)\n");

        printf("Args: ");
        if (cmd->args && cmd->args[0])
        {
            i = 0;
            while (cmd->args[i])
                printf("[%s] ", cmd->args[i++]);
        }
        else
            printf("(none)");
        printf("\n");

        // print combined redirection files list with type
        print_files_list(cmd->files);

        // print heredoc delimiters list with label
        print_str_list(cmd->heredoc_del, "Heredocs");

        printf("Heredoc flag: %d\n", cmd->heredoc);
        printf("Pipe: %d\n", cmd->pipe);
        printf("-------------\n");

        cmd = cmd->next;
    }
    printf("-----------------------------------------------------------------------\n");
}
