# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/11 23:11:34 by junghan           #+#    #+#              #
#    Updated: 2021/09/11 23:11:36 by junghan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES: .c .o

NAME = libft.a
SRCS = ft_bzero.c \
	   ft_strlen.c \
	   ft_strlcpy.c \
	   ft_strlcat.c \
	   ft_atoi.c \
	   ft_calloc.c \
	   ft_strdup.c \
	   ft_strjoin.c \
	   ft_itoa.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -c

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: bonus clean fclean all re
