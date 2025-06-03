# barca		4	|	3		real madrid  waaaa333333 hhhhhhhhhhhhhhhhhhhhhhhhhhh

SRCS	= Minishell.c parsing_part/clean_up/trash_can.c parsing_part/clean_up/utils.c \
parsing_part/parsing/making_tokens.c parsing_part/parsing/making_cmds.c \
parsing_part/parsing/making_envs.c parsing_part/parsing/parsing.c \
parsing_part/parsing/helping_functions/utils1.c parsing_part/parsing/helping_functions/utils2.c \
parsing_part/parsing/helping_functions/utils3.c parsing_part/parsing/helping_functions/utils4.c \
parsing_part/parsing/helping_functions/utils5.c parsing_part/parsing/syntax_errors/invalid_syntax.c \
parsing_part/parsing/syntax_errors/utils2.c parsing_part/parsing/syntax_errors/syntax_error.c \
parsing_part/parsing/syntax_errors/utils1.c parsing_part/utils/data_init.c \
parsing_part/utils/ft_error.c parsing_part/utils/ft_lstadd_back.c parsing_part/utils/ft_lstlast.c \
parsing_part/utils/ft_lstnew.c parsing_part/utils/ft_split.c parsing_part/utils/ft_strcmp.c \
parsing_part/utils/ft_strdup.c parsing_part/utils/ft_strlen.c parsing_part/utils/ft_strsdup.c \
parsing_part/utils/ft_substr.c parsing_part/utils/skip_it.c parsing_part/utils/symbols.c \
parsing_part/utils/ft_isalnum.c parsing_part/utils/ft_isalpha.c parsing_part/utils/ft_isdigit.c \
parsing_part/utils/ft_strjoin.c parsing_part/utils/ft_itoa.c parsing_part/parsing/expending/expending.c \
parsing_part/parsing/helping_functions/utils6.c \
parsing_part/test_functions/print_tokens.c \
parsing_part/test_functions/print_cmds.c \
parsing_part/test_functions/print_envs.c \
parsing_part/test_functions/print_strs.c \


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