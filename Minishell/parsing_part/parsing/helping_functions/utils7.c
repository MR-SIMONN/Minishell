/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 00:46:30 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/13 22:40:14 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

char    *delete_random_quotes(char *s, t_data *d)
{
    int i;
    int j;
    int len;
    char *str;

    i = 0;
    j = 0;
    len = ft_strlen(s) - quotes_len(s);
    // printf ("IIIIIIIIIIIIIIIIIIII nooottt  normal -->  %d - %d = %d\n", (int)ft_strlen(s),+ quotes_len(s), len);
    str = ft_malloc(len + 1, d);
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '\"')
            i++;
        if (s[i] && s[i] != '\'' && s[i] != '\"')
            str[j++] = s[i++];
    }
    return (str[j] = '\0', str);
}

char    *delete_quotes(char *s, t_data *d)
{
    int     i;
    int     j;
    int     len;
    char    *str;
    char    c;

    // printf ("IIIIIIIIIIIIIIIIIIII   normal\n");
    i = 1;
    j = 0;
    len = ft_strlen(s) - 2;
    str = ft_malloc(len + 1, d);
    c = s[0];
    while (s[i + 1])
    {
        if (s[i] != c)
            str[j++] = s[i];
        i++;
    }
    str[j] = '\0';
    return (str);
}
void    get_rid_of_quotes(t_token *t, t_data *d)
{
    while (t)
    {
        if ((t->value[0] == '\'' && t->value[ft_strlen(t->value) - 1] == '\'') 
            || (t->value[0] == '\"' && t->value[ft_strlen(t->value) - 1] == '\"'))
            t->value = delete_quotes(t->value, d);
        else
            t->value = delete_random_quotes(t->value, d);
        t = t->next;
    }
}
void	handle_sigint(int sig)
{
	(void)sig;
	printf ("\n");
    // rl_replace_line("", 0);
	rl_on_new_line();   // move readline to new line
	rl_redisplay(); // redraw prompt
}

void    signal_stuff()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}