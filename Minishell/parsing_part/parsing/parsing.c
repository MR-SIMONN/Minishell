/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:59:55 by moel-hai          #+#    #+#             */
/*   Updated: 2025/07/14 21:33:25 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	parsing(t_data *d)
{
	if (!d)
		return (1);
	if (empty_cmd(d->line))
		return (1);
	if (is_invalid_syntax(d->line))
		return (syntax_error("syntax error"));
	ft_lst_tokens (d);
	if (handle_syntax_error(d->token, d))
		return (syntax_error("syntax error"));
	after_redir_tokens(d->token);
	after_export_tokens(d->token);
	return (0);
}
