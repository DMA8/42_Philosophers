SRC = philo.c

OBJ = $(SRC:.c=.o)
NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
		rm -f $(OBJ)
fclean: clean
		rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re