
#include "../Minishell.h"

t_token_type    token_type(char *s)
{
    int i;

    i = 0;
    if (is_one_symbol(s, 0))
    {
        if (s[0] == '|')
            return (TOKEN_PIPE);
        else if (s[0] == '>')
            return (TOKEN_REDIRECT_OUT);
        else if (s[0] == '<')
            return (TOKEN_REDIRECT_IN);
    }
    else if (is_two_symbols(s, 0))
    {
        if (s[0] == '>')
            return (TOKEN_APPEND);
        else if (s[0] == '<')
            return (TOKEN_HEREDOC);
    }
    else
        return (TOKEN_WORD);
}

t_list	*ft_lstnew(char *content, t_data *d)
{
	t_token	*s;

	s = (t_token *)ft_malloc(sizeof(t_token), d);
	s->value = content;
	s->type = token_type(content);
	s->next = NULL;
	return (s);
}
