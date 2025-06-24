/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:30:54 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/24 02:30:53 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

void	make_backup_env(t_env **envs, t_data *d)
{
	char	*pwd;

	pwd = NULL;
	if (getcwd(pwd, 1024))
		env_add_back(envs, new_env(ft_strjoin("PWD=", pwd, d), d));
	else
		env_add_back(envs, new_env("PWD=/", d));
	env_add_back(envs, new_env("SHLVL=1", d));
	env_add_back(envs, new_env(ft_strjoin("_=",
				ft_strjoin(pwd, "/Minishell", d), d), d));
	env_add_back(envs, new_env(ft_strjoin("PATH=", THE_PATH, d), d));
}

int	valid_key(char c)
{
	return (c && c != ' ' && c != '$');
}

int	quotes_len(char *s)
{
	int		i;
	char	c;
	int		flag;
	int		len;

	i = 0;
	len = 0;
	flag = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && !flag)
		{
			c = s[i];
			flag = 1;
		}
		else if (s[i] == c && flag)
		{
			flag = 0;
			len += 2;
		}
		i++;
	}
	return (len);
}

int	is_word(t_token *t)
{
	return ((t->type == WORD || is_quoted (t->type)
			|| t->type == VAR || t->type == D_VAR)
		|| t->type == S_VAR) || t->type == EXPENDED;
}
void	split_to_toknes(t_token **t, t_data *d)
{
    char	**parts;
    t_token *curr;
    t_token *next;
    int     i;

    curr  = *t;
    parts = ft_split(curr->value, d);
    if (!parts)
        return;

    // 1) replace current token with first part
    curr->value = parts[0];
    curr->type  = WORD;

    // remember what was after this token
    next = curr->next;

    // 2) for each remaining part, make a new token and splice it in
    i = 1;
    while (parts[i])
    {
        t_token *node = ft_lstnew(parts[i], d, 0);
        // ft_lstnew with quote=0 gives you a WORD token

        curr->next = node;
        node->next = next;
        curr       = node;
        i++;
    }
}
