SRCS	= Minishell.c ##utils.c

NAME = Minishell

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

DEPS = Minishell.h

all: $(NAME)

%.o: %.c ${DEPS}
	cc ${FLAGS} -c $< -o $@

$(NAME) : $(OBJS)
	cc $^ ${FLAGS} -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean