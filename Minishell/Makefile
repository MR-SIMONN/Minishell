# barca		4	|	3		real madrid  waaaa333333 hhhhhhhhhhhhhhhhhhhhhhhhhhh

SRCS	= Minishell.c clean_up/trash_can.c clean_up/utils.c parsing/making_tokens.c parsing/making_cmds.c \
parsing/making_envs.c parsing/parsing.c parsing/helping_functions/utils1.c parsing/helping_functions/utils2.c \
parsing/helping_functions/utils3.c parsing/helping_functions/utils4.c parsing/syntax_errors/invalid_syntax.c \
parsing/syntax_errors/syntax_error.c parsing/syntax_errors/utils.c utils/data_init.c \
utils/ft_error.c utils/ft_lstadd_back.c utils/ft_lstlast.c utils/ft_lstnew.c utils/ft_split.c \
utils/ft_strcmp.c utils/ft_strdup.c utils/ft_strlen.c utils/ft_strsdup.c utils/ft_substr.c \
utils/skip_it.c utils/symbols.c utils/ft_isalnum.c utils/ft_isalpha.c utils/ft_isdigit.c \
parsing/expending/expending.c \
test_functions/print_tokens.c \
test_functions/print_cmds.c \
test_functions/print_envs.c \
test_functions/print_strs.c \


NAME = Minishell

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

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

del:
	@rm -f $(NAME)

do: del all clean
	@clear
	@./Minishell