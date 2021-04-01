# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 16:07:58 by junghan           #+#    #+#              #
#    Updated: 2021/04/02 04:43:38 by junghan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES: .c .o

NAME = cub3D

NAME_BONUS = cub3D_bonus

SRCS = ft_main_loop.c ft_calc_floor.c\
	   ft_calc_sprite.c	ft_free_alloc.c ft_mlx_funcs.c \
	   ft_calc_sprite2.c ft_get_args.c \
	   ft_calc_wall.c ft_init_n_alloc.c ft_parse_map.c \
	   ft_calc_wall2.c ft_key_update.c ft_read_mapinfo.c \
	   ft_check_map.c ft_key_update2.c ft_rgb_texture.c \
	   ft_cub_utill.c ft_save_bmp.c \
	   ft_cub_utill2.c \
	   ../gnl/get_next_line.c ../gnl/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

BONUS = ../bonus/ft_fc_draw_bonus.c ../bonus/ft_make_shadow_bonus.c  ../bonus/ft_main_loop_bonus.c \
	   ../bonus/ft_calc_sprite_bonus.c  ../bonus/ft_free_alloc_bonus.c  ../bonus/ft_mlx_funcs_bonus.c \
	    ../bonus/ft_calc_sprite2_bonus.c  ../bonus/ft_get_args_bonus.c  ../bonus/ft_mouse_bonus.c \
	    ../bonus/ft_calc_wall_bonus.c  ../bonus/ft_init_bonus.c  ../bonus/ft_parse_map_bonus.c \
	    ../bonus/ft_calc_wall2_bonus.c  ../bonus/ft_key_update_bonus.c  ../bonus/ft_read_mapinfo_bonus.c \
	    ../bonus/ft_check_map_bonus.c  ../bonus/ft_key_update2_bonus.c  ../bonus/ft_rgb_texture_bonus.c \
	    ../bonus/ft_cub_utill_bonus.c  ../bonus/ft_key_update3_bonus.c  ../bonus/ft_save_bmp_bonus.c \
	    ../bonus/ft_cub_utill2_bonus.c  ../bonus/ft_pop_up_bonus.c  ../bonus/ft_minimap_bonus.c  ../bonus/ft_stage_bonus.c\
	    ../bonus/ft_texalloc_bonus.c  ../bonus/ft_yorn_bonus.c  ../bonus/ft_alloc_bonus.c  ../bonus/ft_sp_texture_bonus.c \
	   ../bonus/ft_pick_item_bonus.c ../bonus/ft_attack_bonus.c ../bonus/ft_weapon_bonus.c ../bonus/ft_stimpack_bonus.c \
	   ../bonus/ft_sound_bonus.c ../bonus/ft_damaged_bonus.c ../bonus/ft_calc_sprite3_bonus.c\
	   ../gnl/get_next_line.c ../gnl/get_next_line_utils.c \

BONUS_OBJS = $(BONUS:.c=.o)

LIBFT = ../libft

LIBFT_LIB = libft.a

MLX = ../mlx

MLX_LIB = libmlx.dylib

INCS = -I ../libft -I ../gnl -I ../mlx

MLXFLAGS = -L. -lmlx -framework OpenGL -framework Appkit -L. -lft

RM = rm -f

LIBC = ar rc

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJS) $(INCS)

bonus :$(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME_BONUS) $(BONUS_OBJS) $(INCS)

$(LIBFT_LIB):
	make all -C $(LIBFT)
	cp ./$(LIBFT)/$(LIBFT_LIB) ./

$(MLX_LIB):
	make all -C $(MLX)
	cp ./$(MLX)/$(MLX_LIB) ./

clean:
	$(RM) $(BONUS_OBJS) $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	make clean -C $(LIBFT)
	make clean -C $(MLX)
	
fclean: clean
	$(RM) $(NAME) $(NAME_BONUS) $(LIBFT_LIB) $(MLX_LIB)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: libft bonus clean fclean all re
