SRCS	= Minishell.c clean_up/trash_can.c clean_up/utils.c parsing/making_tokens.c parsing/making_cmds.c \
parsing/parsing.c parsing/utils.c parsing/syntax_errors/invalid_syntax.c parsing/syntax_errors/syntax_error.c \
parsing/syntax_errors/utils.c utils/data_init.c utils/ft_error.c utils/ft_lstadd_back.c \
utils/ft_lstlast.c utils/ft_lstnew.c utils/ft_split.c utils/ft_strcmp.c utils/ft_strlen.c \
utils/ft_strsdup.c utils/ft_substr.c utils/skip_it.c utils/symbols.c print_tokens.c


NAME = Minishell

OBJS = $(SRCS:%.c=%.o)

FLAGS = -g -Wall -Wextra -Werror #-fsanitize=address -g

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