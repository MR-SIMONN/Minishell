/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:19:40 by moel-hai          #+#    #+#             */
/*   Updated: 2025/07/01 01:46:22 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

void	expend_it(t_token *t, char *key, int index, t_data *d)
{
	t_expend_infos	infos;

	if (!var_value(d->env, key, d))
		return ;
	if (key[0] == '?')
		index++;
	else
		while (t->value[index] && valid_char(t->value[index]))
			index++;
	infos.s = t->value;
	infos.env_value = var_value(d->env, key, d);
	infos.d = d;
	infos.after_key = index;
	infos.key = key;
	infos.len = expended_token_len(d, t->value, key, index);
	t->value = new_expended_token(infos);
	if (t->type != REDIR_VAR)
	{
		if (t->type == EXPORT_ARG)
			t->type = EX_EXP_ARG;
		else
			t->type = EXPENDED;
	}
}

char	*delete_invalid_var(char *str, t_data *d)
{
	int		i;
	int		j;
	int		len;
	char	*s;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	len = decrease_len(str);
	s = ft_malloc(len + 1, d);
	while (str[i])
	{
		if (str[i] == '$' && !flag)
		{
			i++;
			while (str[i] && valid_char(str[i]))
				i++;
			flag = 1;
		}
		else if (str[i])
			s[j++] = str[i++];
	}
	return (s[j] = '\0', s);
}

int	check_var(t_token *t, int i, t_data *d)
{
	char	*s;

	s = copy_var_name(t->value, i + 1, d);
	if (valid_var(s, d->env))
		expend_it(t, s, i + 1, d);
	else
	{
		t->value = delete_invalid_var(t->value, d);
		if (t->type == REDIR_VAR && !t->value[0])
			return (ambiguous_error(s), 1);
		return (0);
	}
	if (t->type == REDIR_VAR && words_count(t->value) > 1
		&& !d_quoted(t->value))
		return (ambiguous_error(s), 1);
	if (space_exists(t->value)
		&& ((t->type == EXPENDED)
			|| (t->type == EX_EXP_ARG && is_splittable(t))))
		split_to_toknes(t, d);
	return (0);
}

int	expending(t_token *t, t_data *d, int s_quote, int d_quote)
{
	int	i;
	int	ambiguous_probleme;

	while (t)
	{
		(1) && (i = 0, s_quote = 0, ambiguous_probleme = 0);
		if (t->type == VAR || t->type == D_VAR || t->type == S_VAR
			|| t->type == REDIR_VAR || t->type == EXPORT_ARG)
		{
			while (t->value[i] && var_count(t->value) > 0)
			{
				if (t->value[i] == '\'' || t->value[i] == '\"')
					quotes_handling(t->value, &i, &s_quote, &d_quote);
				else if (t->value[i] && t->value[i] == '$'
					&& is_var(t->value[i + 1]) && !s_quote)
					ambiguous_probleme = check_var(t, i, d);
				else
					i++;
				if (ambiguous_probleme)
					return (1);
			}
		}
		t = t->next;
	}
	return (0);
}
