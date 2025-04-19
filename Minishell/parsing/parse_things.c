/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_things.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:36:02 by ielouarr          #+#    #+#             */
/*   Updated: 2025/04/20 15:47:54 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void extract_word_from_quotes(int *index, char *line, char quote_type, t_token **list)
{
    char    *allocate;
    int     start;
    int     i;

    i = *index;
    start = i;

    while (line[i] && line[i] != quote_type)
        i++;
    if (line[i] != quote_type)
        ft_error("syntax error: unclosed quote");

    allocate = ft_substr(line, start, i - start);
    if(!allocate)
        ft_error("sorry there is problems happen in backend");
    add_token(allocate, TOKEN_WORD);
    *index = i + 1;
}
void extract_operator_token(const char *line, int *i, t_token **list)
{
    if (line[*i] == '>' && line[*i + 1] == '>')
    {
        add_token(">>", TOKEN_APPEND);
        *i += 2;
    }
    else if (line[*i] == '<' && line[*i + 1] == '<')
    {
        add_token("<<", TOKEN_HEREDOC);
        *i += 2;
    }
    else if (line[*i] == '>')
    {
        add_token(">", TOKEN_REDIRECT_OUT);
        (*i)++;
    }
    else if (line[*i] == '<')
    {
        add_token("<", TOKEN_REDIRECT_IN);
        (*i)++;
    }
    else if (line[*i] == '|')
    {
        add_token("|", TOKEN_PIPE);
        (*i)++;
    }
}

int strings_to_token(char *line, t_token **va_list)
{
    int     i = 0;
    char    *word;
    t_token *list;

    list = NULL;
    while (line[i])
    {
        while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
            i++;
        if (line[i] == '\'' || line[i] == '\"')
        {
            char quote_type = line[i];
            i++;
            extract_word_from_quotes(&i, line, quote_type, list);

        }
        if(line[i] == '|' || line[i] == '<' || line[i] == '>')
        {
           extract_operator_token(line, &i, list);
        }
    }
    return (0);
}
