SRCS	= minishell.c utils.c trash_can.c

NAME = Minishell

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror -lreadline

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