# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 16:07:58 by junghan           #+#    #+#              #
#    Updated: 2021/04/02 01:01:09 by junghan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES: .c .o

NAME = cub3D

NAME_BONUS = cub3D2

SRCS = ft_main_loop.c ft_calc_floor.c\
	   ft_calc_sprite.c	ft_free_alloc.c ft_mlx_funcs.c \
	   ft_calc_sprite2.c ft_get_args.c \
	   ft_calc_wall.c ft_init_n_alloc.c ft_parse_map.c \
	   ft_calc_wall2.c ft_key_update.c ft_read_mapinfo.c \
	   ft_check_map.c ft_key_update2.c ft_rgb_texture.c \
	   ft_cub_utill.c ft_save_bmp.c \
	   ft_cub_utill2.c \
	   ../gnl/get_next_line.c ../gnl/get_next_line_utils.c \


BONUS = ../bonus/ft_make_shadow.c  ../bonus/ft_main_loop.c \
	   ../bonus/ft_calc_sprite.c  ../bonus/ft_free_alloc.c  ../bonus/ft_mlx_funcs.c \
	    ../bonus/ft_calc_sprite2.c  ../bonus/ft_get_args.c  ../bonus/ft_mouse.c \
	    ../bonus/ft_calc_wall.c  ../bonus/ft_init.c  ../bonus/ft_parse_map.c \
	    ../bonus/ft_calc_wall2.c  ../bonus/ft_key_update.c  ../bonus/ft_read_mapinfo.c \
	    ../bonus/ft_check_map.c  ../bonus/ft_key_update2.c  ../bonus/ft_rgb_texture.c \
	    ../bonus/ft_cub_utill.c  ../bonus/ft_key_update3.c  ../bonus/ft_save_bmp.c \
	    ../bonus/ft_cub_utill2.c  ../bonus/ft_pop_up.c  ../bonus/ft_minimap.c ft_stage.c\
	    ../bonus/ft_texalloc.c  ../bonus/ft_yorn.c  ../bonus/ft_alloc.c  ../bonus/ft_sp_texture.c \
	   ../bonus/ft_pick_item.c ../bonus/ft_attack.c ../bonus/ft_weapon.c ../bonus/ft_stimpack.c \
	   ../bonus/ft_sound.c ../bonus/ft_damaged.c ../bonus/ft_calc_sprite3.c\
	   ../gnl/get_next_line.c ../gnl/get_next_line_utils.c \

BONUS_OBJS = ../../$(BONUS:.c=.o)


LIBFT = ../libft

LIBFT_LIB = libft.a

MLX = ../mlx

MLX_LIB = libmlx.dylib

INCS = -I ../libft -I ../gnl -I ../mlx

OBJS = $(SRCS:.c=.o)

MLXFLAGS = -L. -lmlx -framework OpenGL -framework Appkit -L. -lft

RM = rm -f

LIBC = ar rc

CC = gcc

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJS) $(INCS)

$(NAME_BONUS): $(BONUS_OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(BONUS_OBJS) $(INCS)

$(LIBFT_LIB):
	make all -C $(LIBFT)
	cp ./$(LIBFT)/$(LIBFT_LIB) ./

$(MLX_LIB):
	make all -C $(MLX)
	cp ./$(MLX)/$(MLX_LIB) ./

all : $(NAME)

clean:
	$(RM) $(BONUS_OBJS) $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	make clean -C $(LIBFT)
	make clean -C $(MLX)
	
fclean: clean
	$(RM) $(NAME) $(BONUS_OBJ) $(LIBFT_LIB) $(MLX_LIB)
	make fclean -C $(LIBFT)

re: fclean all

bonus: $(BONUS_OBJS) 
	fclean
	$(NAME_BONUS) $(BONUS_OBJS) 

.PHONY: libft bonus clean fclean all re
