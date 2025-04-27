/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:48:06 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/27 22:50:38 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char *get_token_type_name(t_token_type type)
{
    if (type == TOKEN_WORD)
        return "WORD";
    if (type == TOKEN_PIPE)
        return "PIPE";
    if (type == TOKEN_REDIRECT_OUT)
        return "REDIRECT_OUT";
    if (type == TOKEN_REDIRECT_IN)
        return "REDIRECT_IN";
    if (type == TOKEN_APPEND)
        return "APPEND";
    if (type == TOKEN_HEREDOC)
        return "HEREDOC";
    return "UNKNOWN";
}

void print_tokens(t_token *head)
{
    if (!head)
        return ;
    printf("\n--- Token List ---\n");
    while (head)
    {
        printf("Token: %-15s                | Type: %-12s\n", head->value, get_token_type_name(head->type));
        head = head->next;
    }
    printf("------------------\n\n");
}