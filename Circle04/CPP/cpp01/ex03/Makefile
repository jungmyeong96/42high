# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 20:23:57 by junghan           #+#    #+#              #
#    Updated: 2021/11/24 20:23:59 by junghan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		violence

CC =		clang++

CXXFLAGS =	-std=c++98 -Wall -Wextra -Werror

SRC =		main.cpp HumanA.cpp HumanB.cpp Weapon.cpp

SRC_PATH =	$(addprefix ./srcs/, $(SRC))

OBJ = 	$(SRC_PATH:.cpp=.o)

INC_PATH = 	./includes

all :		$(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CXXFLAGS) -I $(INC_PATH) -o $@ $^

clean :
			rm -f $(OBJ)

fclean :	clean
			rm -f $(NAME)

re :		fclean all

.PHONY :	all clean fclean re
