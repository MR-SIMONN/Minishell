/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:17:27 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/07 00:47:12 by moel-hai         ###   ########.fr       */
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

typedef struct s_heap
{
    void    *address;
    struct s_heap   *next;
}   t_heap;

// token.h or in Minishell.h

typedef enum e_token_type
{
    QUOTED,         // a quoted string
    WORD,           // a normal string
    PIPE,           // |
    REDIRECT_OUT,   // >
    REDIRECT_IN,    // <
    APPEND,         // >>
    HEREDOC         // <<
} t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

typedef struct s_cmd 
{
    char            *cmd;
    char            **args;
    char            *infile;
    char            *outfile;
    int             append;
    int             heredoc;
    char            *heredoc_del;
    int             pipe;
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_data
{
    char    *line;
    t_heap  *heap;
    t_token *token;
    t_cmd  *cmds;
    // char    *path;
    // more data needed tho
}   t_data;

//parsing functions
int     parsing(t_data *d);
int     empty_cmd(char *s);
int     is_invalid_syntax(char *s, t_data *d);
void    fill_d_cmd(t_cmd *cmd, t_token *t, t_data *d);
int     check_one(char *s, int i, t_data *d);
int     check_two(char *s, int i, t_data *d);
int     is_symbol(char c);
void    ft_lst_tokens(t_data *d);
void    ft_error(char *message);
void    handle_symbols(char *s, int *len, int i);
int     is_two_symbols(char *s, int i);
int     is_one_symbol(char *s, int i);
void    set_strcut_values(t_data *d);
void    skip_it(char *s, int *i, char c);
int     handle_syntax_error(t_token *t, t_data *d);
int     syntax_error (char *s, t_data *d);

//garbage collector functions
void	free_everything(t_data *data, int i);
void	clear_trash(t_heap **lst);
void	store_addr(char *s, t_data *data);
void	*ft_malloc(size_t size, t_data *data);
void	free_all(char **s, int i);

//libft functions
int     ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1, t_data *d);
size_t  ft_strlen (char *str);
char	*ft_substr(char *s, unsigned int start, size_t len, t_data *data);
char	**ft_split(char *s, char c, t_data *d);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token *ft_lstnew(char *content, t_data *d, int quote);
t_token	*ft_lstlast(t_token *lst);
char	*ft_strsdup(char *s1, int l, t_data *d);

//testing functions
void    print_tokens(t_token *head);

# endif