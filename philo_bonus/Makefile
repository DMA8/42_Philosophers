# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syolando <syolando@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/21 01:52:10 by syolando          #+#    #+#              #
#    Updated: 2022/05/30 01:37:40 by syolando         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	philo_bonus.c\
		inits_bonus.c\
		lifecycle_bonus.c\
		timefuncs_bonus.c\
		print_bonus.c\
		kill_processes_bonus.c\
		validation_bonus/validate_inputs_bonus.c\
		validation_bonus/utils_bonus.c\


OBJ = $(SRC:.c=.o)
NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
HEADER = philo_bonus.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
		rm -f $(OBJ)
fclean: clean
		rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re