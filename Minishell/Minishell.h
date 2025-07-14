/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:17:27 by moel-hai          #+#    #+#             */
/*   Updated: 2025/07/14 17:04:42 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

# define THE_PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

typedef struct s_heap
{
	void			*address;
	struct s_heap	*next;
}	t_heap;

typedef enum e_token_type
{
	EX_EXP_ARG,
	EXPORT_ARG,
	EXPENDED,
	VAR,
	S_VAR,
	D_VAR,
	S_QUOTED,
	D_QUOTED,
	REDIR_WORD,
	D_REDIR_WORD,
	S_REDIR_WORD,
	REDIR_VAR,
	WORD,
	PIPE,
	REDIRECT_OUT,
	REDIRECT_IN,
	APPEND,
	HEREDOC
}	t_token_type;

typedef enum e_redir_type
{
	OUT_FILE,
	IN_FILE,
	APPEND_FILE,
	HERDOC_DEL
}	t_redir_type;

typedef struct s_str
{
	char			*s;
	int				expendable;
	t_redir_type	type;
	struct s_str	*next;
}	t_str;

typedef struct s_fds
{
	int	input_fd;
	int	output_fd;
}	t_fds;

typedef struct s_pipe
{
	int	fds[2];
}	t_pipe;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*both;
	struct s_env	*next;
}	t_env;

typedef struct s_exp
{
	char			*value;
	struct s_exp	*next;
}	t_exp;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_str			*files;
	int				heredoc;
	t_str			*heredoc_del;
	char			*heredocfilename;
	int				finalfd;
	int				pipe;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	*line;
	t_heap	*heap;
	t_token	*token;
	t_cmd	*cmds;
	t_env	*env;
	t_exp	*exp;
	t_pipe	*pipes;
}	t_data;

typedef struct s_expend_infos
{
	char	*s;
	char	*env_value;
	int		len;
	t_data	*d;
	int		after_key;
	char	*key;
}	t_expend_infos;

int		parsing(t_data *d);
int		empty_cmd(char *s);
int		emty_token(char *s, t_token_type type);
int		is_invalid_syntax(char *s);
int		parentheses(char *s);
void	after_redir_tokens(t_token *t);
void	ft_lst_tokens(t_data *d);
void	store_envs(t_env **envs, char **env, t_data *d);
int		expending(t_token *t, t_data *d, int s_quote, int d_quote);
char	*expand_heredoc(char *s, t_data *d);
int		expended_token_len(t_data *d, char *s, char *key, int i);
char	*new_expended_token(t_expend_infos infos);
void	fill_d_cmd(t_cmd **c, t_token *t, t_data *d);
int		args_len(t_token *t);
void	copy_args(char **args, t_token *t, t_data *d);
int		check_one(char *s, int i);
int		check_two(char *s, int i);
int		is_symbol(char c);
void	handle_symbols(char *s, int *len, int i);
int		is_two_symbols(char *s, int i);
int		is_one_symbol(char *s, int i);
void	set_strcut_values(t_data *d, int i);
int		handle_syntax_error(t_token *t, t_data *d);
int		syntax_error(char *s);
void	get_rid_of_quotes(t_token *t, t_data *d);
char	*delete_invalid_var(char *str, t_data *d);
void	ambiguous_error(char *str);
void	signal_stuff(void);
void	handle_sigint(int sig);
void	split_to_toknes(t_token *curr, t_data *d);
void	after_export_tokens(t_token *t);
int		is_splittable(t_token *t);
int		d_quoted(char *s);
int		is_value_quoted(char *s);
int		is_key_quoted(char *s);
t_str	*new_strnode(char *string, t_token *t, t_data *d);
void	ft_cmdadd_back(t_cmd **c, t_cmd *new);
t_str	*last_str(t_str *p);
void	env_add_back(t_env **envs, t_env *new);
int		is_quoted(t_token_type type);
void	quotes_stuff(char *s, int i, char *c, int *quotes);
int		valid_char(char c);
char	*copy_var_name(char *s, int i, t_data *d);
int		valid_var(char *s, t_env *env);
char	*var_value(t_env *env, char *key, t_data *d);
void	ignore_tokens(t_token **head);
int		var_count(char *s);
int		decrease_len(char *s);
int		is_var(char c);
t_env	*new_env(char *s, t_data *d);
int		valid_key(char c);
int		quotes_len(char *s);
int		is_word(t_token *t);
char	*delete_quotes(char *s, char c, int flag, t_data *d);
int		exit_status(int should_update, int new_status);
void	quotes_handling(char *s, int *i, int *s_quote, int *d_quote);
int		space_exists(char *s);
int		words_count(char *str);
int		is_space(char c);
void	skip_spaces(char *s, int *i);
void	free_everything(t_data *data, int i);
void	clear_trash(t_heap *lst);
void	store_addr(char *s, t_data *data);
void	*ft_malloc(size_t size, t_data *data);
char	*ft_strjoin(char *s1, char *s2, t_data *d);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, char *s2, size_t ncmp);
char	*ft_strdup(char *s1, t_data *d);
size_t	ft_strlen(char *str);
char	*ft_substr(char *s, unsigned int start, size_t len, t_data *data);
char	**ft_split(char *s, t_data *d);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstnew(char *content, t_data *d, int quote);
t_token	*ft_lstlast(t_token *lst);
char	*ft_strsdup(char *s1, int l, t_data *d);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
char	*ft_itoa(int n, t_data *d);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, char *needle, size_t len);
int		execution(t_data *d);
int		is_builtin(char *cmd);
int		execute_builtin(char *cmd, char **args, t_data *d);
int		cd_v(char **args, t_data *d);
int		echo_v(char **args);
void	env_v(t_env *list, char **args);
void	exit_v(char **args, t_data *d);
int		pwd_v(t_data *d);
int		export_v(t_data *d, char **args);
int		unset_v(t_data *d, char **args);
int		is_digit(const char *str);
long	ft_atol(const char *str, int *range_check);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin_eq(char *s1, char *s2, t_data *d);
t_env	*ft_lstnew_export_to_env(char *key, char *value, char *both, t_data *d);
t_exp	*ft_lstnew_export_to_value(char *value, t_data *d);
t_env	*ft_env_lstlast(t_env *lst);
void	ft_env_lstadd_back(t_env **lst, t_env *new);
t_exp	*ft_exp_lstlast(t_exp *lst);
void	ft_exp_lstadd_back(t_exp **lst, t_exp *new);
void	remove_from_env_lst(t_env **env_lst, char *key);
void	remove_from_export_lst(t_exp **exp_lst, char *key);
t_exp	*find_exp_node(t_exp *exp_lst, char *key);
t_env	*find_env_node(t_env *env_lst, char *key);
int		is_exported(t_exp *exp_lst, t_env *env_lst, char *key);
int		is_valid_identifier(char *str, int len);
char	**get_path(t_data *d);
char	*get_fullpath(char *path, char *command, t_data *d);
char	**ft_splits(char *str, char delimiter, t_data *d);
void	duping(int saved_stdin, int saved_stdout);
void	permission_denied_error(char *path);
void	command_not_found_error(char *cmd);
void	this_is_a_directory(char *path);
void	not_a_directory(char *cmd);
void	not_found(char *cmd);
int		num_arg_req(char *arg);
char	*right_path(char **path, t_cmd *cmds, t_data *d, int *status);
int		setup_redirections(int input_fd, int output_fd);
int		apply_heredoc(t_cmd *cmd, t_data *d, int index);
int		apply_input_redirection(t_str *infiles);
int		apply_heredoc_redirection(t_cmd *cmd);
int		process_heredocs_before_fork(t_data *d);
void	unlink_all_heredocfiles(t_cmd *cmds);
int		execute_single_cmd(t_cmd *cmd, t_data *d, t_fds fds);
int		execute_external_cmd(t_cmd *cmd, t_data *d);
int		has_pipeline(t_cmd *cmds);
int		execute_single_builtin(t_cmd *cmds, t_data *d);
int		execute_single_external(t_cmd *cmds, t_data *d);
int		execute_pipeline(t_data *d);
char	**get_env(t_data *d);
int		count_commands(t_cmd *cmds);
int		execute_pipeline_commands(t_data *d, int cmd_count);
int		apply_redirections(t_str *files, t_cmd *cmd);
int		is_exec(char *path, t_cmd *cmds, int silent, int *status);
int		last_char(char *path);
int		ft_input_fd(int input_fd);
int		ft_output_fd(int input_fd);
int		apply_input_redirection(t_str *files);
int		apply_output_redirection(t_str *files, t_cmd *cmd);
int		ft_has_no_pipe(t_data *d);
void	ft_file(t_cmd *cmd, int index, t_data *d, int *fd);
char	*handle_no_path(t_cmd *cmds, t_data *d, int *status);
void	ft_expand_heredoc_handler(t_str *current, int fd, t_data *d);
int		is_valid_identifier(char *str, int len);
void	export_displayer(t_env *env_lst, t_exp *exp_lst);
void	handle_export_only(char *arg, t_data *d);
void	add_or_update_env(t_data *d, char *key, char *value);
void	append_to_existing_env(t_env *existing, char *key, char *append_value,
			t_data *d);
void	create_new_env_node(t_data *d, char *key, char *value);
void	update_env_value(t_env *node, char *new_value, char *new_both);
void	prepare_pipe(int *pipe_fd, int need_pipe);
int		setup_child_fds(int in_fd, int *pipe_fd);
int		wait_for_children(pid_t *pids, int cmd_count);
void	wait_childrens(pid_t *pids, int i);
void	close_fds_after_use(int in_fd, int pipe_fd);
char	*remove_trailing_slash(char *path, t_data *d);
int		slash_char(char *path);
int		sig_check(int update_it, int new_value);
void	make_backup_env(t_env **envs, t_data *d);
#endif
