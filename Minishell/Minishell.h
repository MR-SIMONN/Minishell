/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:17:27 by moel-hai          #+#    #+#             */
/*   Updated: 2025/06/13 21:28:34 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//wach ma3ndk mayddar tabe3ni hhhhhh wasafi sir lmakefile ghatl9a comment mohim lfoo9

# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

# define THE_PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

typedef struct s_heap
{
	void    *address;
	struct s_heap   *next;
}   t_heap;

// token.h or in Minishell.h

typedef enum e_token_type
{
    VAR,            // a string contanis a variable
    S_VAR,          // a single quoted string contanis a variable
    D_VAR,          // a dubble quoted string contanis a variable
    S_QUOTED,       // a single quoted string
    D_QUOTED,       // a dubble quoted string
    REDIR_WORD,     // a string after a red
    D_REDIR_WORD,   // a dubble quoted string after a red
    S_REDIR_WORD,   // a single quoted string after a red
    WORD,           // a normal string
    PIPE,           // |
    REDIRECT_OUT,   // >
    REDIRECT_IN,    // <
    APPEND,         // >>
    HEREDOC         // <<
} t_token_type;

typedef struct s_str
{
	char            *s;
    int             expendable;
	struct s_str    *next;
} t_str;

typedef struct s_env
{
    char            *key;   //USER=
    char            *value; //=moel-hai || ielouarr hhhhh
    char            *both;  //USER=moel-hai || ielouarr hhhhh
    struct s_env    *next;
} t_env;

typedef struct s_exp
{ 
	char            *value; //declare -x {{      a      }} <- this value
	struct s_exp    *next;
} t_exp;

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
	t_str           *infile;
	t_str           *outfile;
	int             append;
	int             heredoc;
	t_str           *heredoc_del;
	int             pipe;
	struct s_cmd    *next;
}   t_cmd;// wafen a khay smail hani kolchi bikhir l3a2ila, fach tchof had lcomment hbet lte7t gaa3 ghatl9a comment wahed khor

typedef struct s_data
{
    char    *line;
    t_heap  *heap;
    t_token *token;
    t_cmd   *cmds;
    t_env   *env;
	t_exp	*exp;
    int     exit_value;
    // more data needed tho
}   t_data;

typedef struct s_expend_infos
{
    char    *s;
    char    *env_value;
    int     len;
    t_data  *d;
    int     after_key;
    char    *key;
} t_expend_infos;

//parsing functions
int     parsing(t_data *d);
int     empty_cmd(char *s);
int     is_invalid_syntax(char *s, t_data *d);
int     parentheses(char *s);
void	change_tokens_types(t_token *t);
void    ft_lst_tokens(t_data *d);
void    store_envs(t_env **envs, char **env, t_data *d);
void    expending(t_token *t, t_data *d, int quote);
int     expended_token_len(t_data *d, char *s, char *key, int i);
char    *new_expended_token(t_expend_infos  infos);
void    fill_d_cmd(t_cmd **c, t_token *t, t_data *d);
int     args_len(t_token *t);
void    copy_args(char **args, t_token *t, t_data *d);
int     check_one(char *s, int i);
int     check_two(char *s, int i);
int     is_symbol(char c);
void    handle_symbols(char *s, int *len, int i);
int     is_two_symbols(char *s, int i);
int     is_one_symbol(char *s, int i);
void    set_strcut_values(t_data *d, int i);
int     handle_syntax_error(t_token *t, t_data *d);
int     syntax_error (char *s);
void	make_backup_env(t_env **envs, t_data *d);
void    get_rid_of_quotes(t_token *t, t_data *d);
char    *delete_invalid_var(char *str, t_data *d);
void    signal_stuff();

//utils functions
t_str	*new_strnode(char *string, t_token *t, t_data *d);
void	ft_cmdadd_back(t_cmd **c, t_cmd   *new);
t_str	*last_str(t_str *p);
void    ft_error(char *message);
void    skip_it(char *s, int *i, char c);
void	env_add_back(t_env **envs, t_env *new);
int     no_pipeout(char *s, int i);
int     no_pipeout_token(t_token *t);
int     is_quoted(t_token_type type);
void    quotes_stuff(char *s, int i, char *c, int *quotes);
int     valid_char(char c);
char    *copy_var_name(char *s, int i, t_data *d);
int     valid_var(char *s, t_env *env);
char    *var_value(t_env *env, char *key, t_data *d);
void	ignore_tokens(t_token **head);
int	    var_count(char *s);
int	    decrease_len(char *s);
int	    is_var(char c);
t_env   *new_env(char *s, t_data *d);
int     valid_key(char c);
int     quotes_len (char *s);
int     is_word(t_token *t);
char    *delete_quotes(char *s, t_data *d);
char    *delete_random_quotes(char *s, t_data *d);

//garbage collector functions
void	free_everything(t_data *data, int i);
void	clear_trash(t_heap **lst);
void	store_addr(char *s, t_data *data);
void	*ft_malloc(size_t size, t_data *data);

//libft functions
char	*ft_strjoin(char *s1, char *s2, t_data *d);
int     ft_strcmp(char *s1, char *s2);
int    ft_strncmp(const char *s1, char *s2, size_t ncmp);
char	*ft_strdup(char *s1, t_data *d);
size_t  ft_strlen (char *str);
char	*ft_substr(char *s, unsigned int start, size_t len, t_data *data);
char	**ft_split(char *s, char c, t_data *d);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token *ft_lstnew(char *content, t_data *d, int quote);
t_token	*ft_lstlast(t_token *lst);
char	*ft_strsdup(char *s1, int l, t_data *d);
int     ft_isalpha(int c);
int     ft_isdigit(int c);
int     ft_isalnum(int c);
char	*ft_itoa(int n, t_data *d);
char    *ft_strchr(const char *s, int c);
char    *ft_strnstr(const char *haystack, char *needle, size_t len);
char    *ft_strjoin(char *s1, char *s2, t_data *d);

//testing functions
void    print_tokens(t_token *head);
void    print_cmds(t_cmd *cmd);
void    print_envs(t_env *env);
void    print_strs(char **s);


//Execution part ; functions :
// int     execution(t_data *data,t_data *cmds, t_data *d);
int    execution(t_env **env,t_cmd *cmds, t_data *d);
int     is_builtin(char *cmd);
int     execute_builtin(char *cmd,t_env **env, char **args, t_data *d);

// bulltin funs
int     cd_v(char **args, t_env **env,t_data *d);
int     echo_v(char **args);
void    env_v(t_env *list);
void    exit_v(char **args);
int        pwd_v(void);
int        export_v(t_env **env_lst, char **args, t_data *d);
int        unset_v(t_env **env_lst, t_data *d ,char **args);
// utils funcs :
int     is_digit(const char *str);
long    ft_atol(const char *str, int *range_check);
void    ft_putstr_fd(char *s, int fd);
char    *ft_strjoin_eq(char *s1, char *s2, t_data *d);
t_env   *ft_lstnew_export_to_env(char *key, char *value, char *both, t_data *d);
t_exp   *ft_lstnew_export_to_value(char *value, t_data *d);
t_env   *ft_env_lstlast(t_env *lst);
void    ft_env_lstadd_back(t_env **lst, t_env *new);
t_exp   *ft_exp_lstlast(t_exp *lst);
void    ft_exp_lstadd_back(t_exp **lst, t_exp *new);
void    remove_from_env_lst(t_env **env_lst, char *key);
void    remove_from_export_lst(t_exp **exp_lst, char *key);
t_exp   *find_exp_node(t_exp *exp_lst, char *key);
t_env   *find_env_node(t_env *env_lst, char *key);
int     is_exported(t_exp *exp_lst, char *key);
# endif
// tle3 lfo9 gaaa3 ghatl9a wahed akhor