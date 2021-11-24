# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 20:23:22 by junghan           #+#    #+#              #
#    Updated: 2021/11/24 20:23:24 by junghan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		main

CC =		clang++

CXXFLAGS =	-std=c++98 -Wall -Wextra -Werror

SRC =		main.cpp

OBJ = 		$(SRC:.cpp=.o)

all :		$(NAME)

$(NAME) : $(OBJ)
		 $(CC) $(CXXFLAGS) -o $@ $^

clean :
			rm -f $(OBJ)

fclean :	clean
			rm -f $(NAME)

re :		fclean all

.PHONY :	all clean fclean re
