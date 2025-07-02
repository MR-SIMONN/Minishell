/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:46 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/30 22:34:00 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	handle_append(t_data *d, char *arg)
{
	int			plus_pos;
	char		*key;
	char		*append_value;
	t_env		*existing;

	plus_pos = 0;
	while (!(arg[plus_pos] == '+' && arg[plus_pos + 1] == '='))
		plus_pos++;
	key = ft_substr(arg, 0, plus_pos, d);
	append_value = ft_substr(arg, plus_pos + 2,
			ft_strlen(arg) - plus_pos - 2, d);
	existing = find_env_node(d->env, key);
	if (existing)
		append_to_existing_env(existing, key, append_value, d);
	else
		create_new_env_node(d, key, append_value);
}

void	handle_assignment(t_data *d, char *arg)
{
	int			eq_pos;
	char		*key;
	char		*value;

	eq_pos = 0;
	while (arg[eq_pos] != '=')
		eq_pos++;
	key = ft_substr(arg, 0, eq_pos, d);
	value = ft_substr(arg, eq_pos + 1,
			ft_strlen(arg) - eq_pos - 1, d);
	add_or_update_env(d, key, value);
}

void	export_cases(t_data *d, char *arg)
{
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		handle_append(d, arg);
	else if (ft_strchr(arg, '='))
		handle_assignment(d, arg);
	else
		handle_export_only(arg, d);
}

void	export_handler(char **args, t_data *d, int *status)
{
	int		i;
	int		j;
	char	*arg;

	i = 1;
	while (args[i])
	{
		arg = args[i];
		j = 0;
		while (arg[j] && arg[j] != '='
			&& !(arg[j] == '+' && arg[j + 1] == '='))
			j++;
		if (!is_valid_identifier(arg, j) || arg[0] == '=')
		{
			printf("export: `%s`: not a valid identifier\n", arg);
			*status = 1;
			i++;
			continue ;
		}
		export_cases(d, arg);
		i++;
	}
}

int	export_v(t_data *d, char **args)
{
	int	status;

	status = 0;
	if (!args[1])
	{
		export_displayer(d->env, d->exp);
		return (exit_status(1, status));
	}
	export_handler(args, d, &status);
	return (exit_status(1, status));
}
