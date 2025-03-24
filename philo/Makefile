NAME = philo
SRC = main.c destroy.c forks.c getters.c setters.c init.c init_philos.c routine.c utils.c
OBJS=$(SRC:.c=.o)
CC = cc
CC_FLAGS = -Wall -Wextra -Werror -pthread

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
