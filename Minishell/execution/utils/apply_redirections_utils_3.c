/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_utils_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 23:29:55 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/29 16:04:36 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	ft_expand_heredoc_handler(t_str *current, int fd, t_data *d)
{
	char	*exp;

	if (current->expendable != 0)
	{
		exp = expand_heredoc(d->line, d);
		ft_putstr_fd(exp, fd);
		ft_putstr_fd("\n", fd);
		if (exp != d->line)
			free(exp);
	}
	else
	{
		ft_putstr_fd(d->line, fd);
		ft_putstr_fd("\n", fd);
	}
}
