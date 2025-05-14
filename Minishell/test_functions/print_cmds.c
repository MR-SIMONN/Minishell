/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 05:38:47 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/14 16:47:14 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	print_str_list(t_str *lst, const char *label)
{
	printf("%s: ", label);
	if (!lst)
	{
		printf("(none)\n");
		return;
	}
	while (lst)
	{
		printf("[%s] ", lst->s);
		lst = lst->next;
	}
	printf("\n");
}

void	print_cmds(t_cmd *cmd)
{
	int	i;

    printf("\n---  cmd list  -------------------------------------------------------\n\n");
	while (cmd)
	{
		printf("---- CMD ----\n");
		
		if (cmd->cmd)
			printf("Cmd: %s\n", cmd->cmd);
		else
			printf("Cmd: (null)\n");

		printf("Args: ");
		if (cmd && cmd->args && cmd->args[0])
		{
			i = 0;
			while (cmd->args[i])
				printf("[%s] ", cmd->args[i++]);
		}
		else
			printf("(none)");
		printf("\n");

		print_str_list(cmd->infile,     "Infiles");
		print_str_list(cmd->outfile,    "Outfiles");
		print_str_list(cmd->heredoc_del,"Heredocs");
		printf("Append: %d\n", cmd->append);
		printf("Heredoc flag: %d\n", cmd->heredoc);
		printf("Pipe: %d\n", cmd->pipe);
		printf("-------------\n");

		cmd = cmd->next;
	}
    printf("-----------------------------------------------------------------------\n");
}