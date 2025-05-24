/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:17:27 by moel-hai          #+#    #+#             */
/*   Updated: 2025/05/24 14:51:13 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//wach ma3ndk mayddar tabe3ni hhhhhh wasafi sir lmakefile ghatl9a comment mohim lfoo9

# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
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
	IGNORED,        //just skip this token just like it doesn't exist :)
	VAR,            // a string contanis $ 
	S_QUOTED,       // a single quoted string
	D_QUOTED,       // a dubble quoted string
	REDIR_WORD,     // a string after a red
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
	struct s_str    *next;
} t_str;

typedef struct s_env
{
	char            *key;   //USER=
	char            *value; //=moel-hai
	char            *both;  //USER=moel-hai
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
	// char    *path;
	// more data needed tho
}   t_data;

//parsing functions
int     parsing(t_data *d);
int     empty_cmd(char *s);
int     is_invalid_syntax(char *s, t_data *d);
void	change_tokens_types(t_token *t);
void    ft_lst_tokens(t_data *d);
void    store_envs(t_env **envs, char **env, t_data *d);
void    expending(t_token *t, t_data *d);
int		expended_token_len(t_env *env, char *s, char *key, int i);
char    *new_expended_token(char *s, char *env_value, int len, t_data *d);
void    fill_d_cmd(t_cmd **c, t_token *t, t_data *d);
int     args_len(t_token *t);
void    copy_args(char **args, t_token *t, t_data *d);
int     check_one(char *s, int i);
int     check_two(char *s, int i);
int     is_symbol(char c);
void    handle_symbols(char *s, int *len, int i);
int     is_two_symbols(char *s, int i);
int     is_one_symbol(char *s, int i);
void    set_strcut_values(t_data *d);
int     handle_syntax_error(t_token *t, t_data *d);
int     syntax_error (char *s);

//utils functions
t_str	*new_strnode(char *string, t_data *d);
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
char    *copy_var(char *s, int i, t_data *d);
int     valid_var(char *s, t_env *env);
char    *var_value(t_env *env, char *key);
void	ignore_tokens(t_token **head);

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
int     ft_isalpha(int c);
int     ft_isdigit(int c);
int     ft_isalnum(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2, t_data *d);

//testing functions
void    print_tokens(t_token *head);
void	print_cmds(t_cmd *cmd);
void	print_envs(t_env *env);
void    print_strs(char **s);



//Execution part ; functions :
// int     execution(t_data *data,t_data *cmds, t_data *d);
int	execution(t_env **env,t_cmd *cmds, t_data *d);
int is_builtin(char *cmd);
int execute_builtin(char *cmd,t_env **env, char **args, t_data *d);

// bulltin funs
int		cd_v(char **args);
int		echo_v(char **args);
void	env_v(t_env *list);
void	exit_v(char **args);
int		pwd_v(void);
int		export_v(t_env **env_lst, char **args, t_data *d);
int		unset_v(t_env **env_lst, t_exp **exp_lst, char **args);
// utils funcs :
int		is_digit(const char *str);
long    ft_atol(const char *str, int *range_check);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin_eq(char *s1, char *s2, t_data *d);
t_env	*ft_lstnew_export_to_env(char *key, char *value, char *both, t_data *d);
t_exp	*ft_lstnew_export_to_value(char *value, t_data *d);
t_env	*ft_env_lstlast(t_env *lst);
void	ft_env_lstadd_back(t_env **lst, t_env *new);
t_exp	*ft_exp_lstlast(t_exp *lst);
void	ft_exp_lstadd_back(t_exp **lst, t_exp *new);
# endif
// tle3 lfo9 gaaa3 ghatl9a wahed akhor
