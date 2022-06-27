# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syolando <syolando@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 20:36:06 by syolando          #+#    #+#              #
#    Updated: 2022/06/28 02:21:32 by syolando         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	philo_bonus.c\
		inits.c\
		lifecycle.c\
		philo_utils.c\
		utils.c\


OBJ = $(SRC:.c=.o)
NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread# -fsanitize=thread -g
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