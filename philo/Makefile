# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syolando <syolando@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/21 01:52:10 by syolando          #+#    #+#              #
#    Updated: 2022/05/29 13:58:39 by syolando         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	philo.c\
		inits.c\
		lifecycle.c\
		timefuncs.c\
		print.c\
		validation/validate_inputs.c\
		validation/utils.c\


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