SRCS = \
Minishell.c \
parsing_part/clean_up/trash_can.c \
parsing_part/clean_up/utils.c \
parsing_part/parsing/making_tokens.c \
parsing_part/parsing/making_cmds.c \
parsing_part/parsing/making_envs.c \
parsing_part/parsing/parsing.c \
parsing_part/parsing/helping_functions/utils1.c \
parsing_part/parsing/helping_functions/utils2.c \
parsing_part/parsing/helping_functions/utils3.c \
parsing_part/parsing/helping_functions/utils4.c \
parsing_part/parsing/helping_functions/utils5.c \
parsing_part/parsing/helping_functions/utils6.c \
parsing_part/parsing/helping_functions/utils7.c \
parsing_part/parsing/helping_functions/utils8.c \
parsing_part/parsing/helping_functions/utils9.c \
parsing_part/parsing/syntax_errors/invalid_syntax.c \
parsing_part/parsing/syntax_errors/utils1.c \
parsing_part/parsing/syntax_errors/utils2.c \
parsing_part/parsing/syntax_errors/syntax_error.c \
parsing_part/parsing/expending/expending.c \
parsing_part/parsing/expending/heredoc.c \
parsing_part/utils/data_init.c \
parsing_part/utils/ft_lstadd_back.c \
parsing_part/utils/ft_lstlast.c \
parsing_part/utils/ft_lstnew.c \
parsing_part/utils/ft_split.c \
parsing_part/utils/ft_strcmp.c \
parsing_part/utils/ft_strdup.c \
parsing_part/utils/ft_strlen.c \
parsing_part/utils/ft_strsdup.c \
parsing_part/utils/ft_substr.c \
parsing_part/utils/skip_it.c \
parsing_part/utils/symbols.c \
parsing_part/utils/ft_isalnum.c \
parsing_part/utils/ft_isalpha.c \
parsing_part/utils/ft_isdigit.c \
parsing_part/utils/ft_strchr.c \
parsing_part/utils/ft_itoa.c \
parsing_part/utils/ft_strnstr.c \
parsing_part/utils/ft_strjoin.c \
parsing_part/utils/ft_strncmp.c \
execution/execution_command.c \
execution/builtins/cd.c \
execution/builtins/echo.c \
execution/builtins/env.c \
execution/builtins/exit.c \
execution/builtins/export.c \
execution/builtins/export.c \
execution/builtins/pwd.c \
execution/builtins/unset.c \
execution/builtin_funs.c \
execution/utils/heredoc_utils.c \
execution/utils/export_utils1.c \
execution/utils/export_utils2.c \
execution/utils/ft_atol.c \
execution/utils/ft_isdigit_pro.c \
execution/utils/ft_putstr_fd.c \
execution/utils/ft_lstnew_export.c \
execution/utils/ft_strjoin.c \
execution/utils/ft_splits.c \
execution/utils/exec_helpers.c \
execution/utils/linked.c \
execution/utils/exp_env_utils.c \
execution/execprt.c \
execution/apply_redirections_of_heredoc.c \
execution/apply_redirections_of_heredoc_2.c \
execution/apply_redirections_1.c \
execution/apply_redirections_2.c \
execution/path_funs_1.c \
execution/path_funs_2.c \
execution/path_funs_3.c \
execution/pipes_funs.c \
execution/pipes_funs2.c \
execution/exec_funs.c	\

NAME = minishell

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

DEPS = Minishell.h

all: $(NAME)

%.o: %.c ${DEPS}
	cc ${FLAGS} -c $< -o $@

$(NAME) : $(OBJS)
	cc $^ ${FLAGS} -lreadline -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean
