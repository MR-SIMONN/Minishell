/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:59:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/27 00:41:30 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	parsing(t_data *d)
{
	if (empty_cmd(d->line))
		return (1);
	if (is_invalid_syntax(d->line, d))
	{
		exit_status(1, 258);
		return (syntax_error("syntax error"));
	}
	ft_lst_tokens (d);
	if (handle_syntax_error(d->token, d))
	{
		exit_status(1, 258);
		return (syntax_error("syntax error"));
	}
	after_redir_tokens(d->token);
	after_export_tokens(d->token);
	return (0);
}
