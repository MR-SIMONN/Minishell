SRCS	= Minishell.c clean_up/trash_can.c clean_up/utils.c parsing/parse_things.c token_fs/utils_token.c utils/ft_error.c utils/ft_substr

NAME = Minishell

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror ##-lreadline

DEPS = Minishell.h

all: $(NAME)

%.o: %.c ${DEPS}
	cc ${FLAGS} -c $< -o $@

$(NAME) : $(OBJS)
	cc $^ ${FLAGS} -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean