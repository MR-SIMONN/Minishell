/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:17:27 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/27 02:21:17 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
// #include <>
// #include <>

// typedef enum s_redir_type {
//     REDIR_IN,       // <
//     REDIR_OUT,      // >
//     REDIR_APPEND,   // >>
//     REDIR_HEREDOC   // <<
// } t_redir_type;

// typedef struct s_redir
// {
//     t_redir_type type;
//     char *file;
//     struct s_redir *next;
// } t_redir;

// typedef struct s_cmd
// {
//     char *cmd;         // command name (e.g., "echo")
//     char **args;       // arguments including cmd
//     t_redir *redir;    // list of redirections
//     bool pipe;         // true if pipe to next
//     struct s_cmd *next;
// } t_cmd;

typedef struct s_heap
{
    void    *address;
    struct s_heap   *next;
}   t_heap;

// token.h or in Minishell.h

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_IN,
    TOKEN_APPEND,
    TOKEN_HEREDOC
} t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

typedef struct s_data
{
    char    *line;
    t_heap  *heap;
    char    *path;
    t_token *token;
    // more data needed tho
}   t_data;

//parsing utils functions
void    ft_lst_tokens(t_data *d);
void    ft_error(char *message);
void    handle_symbols(char *s, int *len, int i);
int     is_two_symbols(char *s, int i);
int     is_one_symbol(char *s, int i);
void    set_strcut_values(t_data *d);
int     quotes_len(char *s, char c);
void    skip_it(char *s, int *i, char c);
// void    handle_syntax_error(char *s);

//garbage collector functions
void	free_everything(t_data *data, int i);
void	clear_trash(t_heap **lst);
void	store_addr(char *s, t_data *data);
void	*ft_malloc(size_t size, t_data *data);
void	free_all(char **s, int i);

//libft functions
int	    ft_strcmp(const char *s1, const char *s2);
size_t     ft_strlen (char *str);
char	*ft_substr(char *s, unsigned int start, size_t len, t_data *data);
char	**ft_split(char *s, char c, t_data *d);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token *ft_lstnew(char *content, t_data *d);
t_token	*ft_lstlast(t_token *lst);
char	*ft_strsdup(char *s1, int l, t_data *d);

//testing functions
void print_tokens(t_token *head);

# endif