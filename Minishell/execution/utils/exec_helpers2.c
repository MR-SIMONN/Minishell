/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:29:14 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/07 09:34:41 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	slash_char(char *path)
{
	int	i;

	i = 0;
	while (path[i] && path[i] != '/')
		i++;
	if ((unsigned long)i != ft_strlen(path))
		return (1);
	return (0);
}

char	*remove_trailing_slash(char *path, t_data *d)
{
	int		len;
	char	*without_slash;

	if (!path)
		return (NULL);
	len = ft_strlen(path);
	while (len > 0 && path[len - 1] == '/')
		len--;
	without_slash = ft_substr(path, 0, len, d);
	return (without_slash);
}

void	not_a_directory(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Not a directory\n", 2);
}
