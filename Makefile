NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = philo.c init.c utils.c routine.c monitor.c cleanup.c
OBJS = $(SRCS:.c=.o)
HEADERS = philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 