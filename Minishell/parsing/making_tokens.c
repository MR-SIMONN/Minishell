/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:34:46 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/16 13:06:53 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char    *delete_quotes(char *s, t_data *d)
{
    int i;
    int j;
    int len;
    char *str;

    i = 1;
    j = 0;
    len = ft_strlen(s) - 2;
    str = ft_malloc(len + 1, d);
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '\"')
            break;
        str[j++] = s[i++];
    }
    str[j] = '\0';
    return (str);
}

void     make_tokens(char **t, t_token **p, t_data *d)
{
    int i;
    int quote;

    i = 0;
	while (t[i])
	{
        quote = 0;
        if (t[i][0] == '\'' || t[i][0] == '\"')
        {
            quote = 1;
            t[i] = delete_quotes(t[i], d);
        }
		ft_lstadd_back(p, ft_lstnew(t[i], d, quote));
		i++;
	}
}

int extra_strlen(char *s)
{
    int i = 0;
    int len = 0;

    while (s[i])
    {
        if (is_two_symbols(s, i))
        {
            handle_symbols(s, &len, i);
            len += 2;
            i++;
        }
        else if (is_one_symbol(s, i))
        {
            if (i > 0 && s[i - 1] != ' ' && no_pipeout(s, i))
                len++;
            if (s[i + 1] && s[i + 1] != ' ' && !is_symbol(s[i + 1]))
                len++;
            len++;
        }
        else
            len++;
        i++;
    }
    return (len);
}

void    ft_lst_tokens(t_data *d)
{
    int len;
    char *str;
    char **tokens;

    len = extra_strlen(d->line);
    printf ("\nlen is ----> %d\n", len);
    str = ft_strsdup(d->line, len, d);
    printf ("\nstr is ----> %s\n", str);
    tokens = ft_split(str, ' ', d);
    // print_strs(tokens);
    make_tokens(tokens, &d->token, d);
}
