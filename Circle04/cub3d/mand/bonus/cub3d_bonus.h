/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 01:58:27 by junghan           #+#    #+#             */
/*   Updated: 2021/04/02 02:10:20 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../mlx/mlx.h"
# include "key_macro_bonus.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "ft_structs_bonus.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
void	error_exit(char *str);
int		ft_only_digit(char *dig);
int		is_space(char *d, t_info *p);
int		ft_check_extation(char *mapfile, char *extation);
void	free_dou(char **str);
void	free_tex(int **arr);
double	ft_max(double a, double b);
double	ft_min(double a, double b);
void	screen_size(t_info *info, char *w, char *h);

void	key_up(t_info *info, t_keys *keys);
void	key_down(t_info *info, t_keys *keys);
void	key_right(t_info *info, t_keys *keys);
void	key_left(t_info *info, t_keys *keys);
void	turn_right(t_info *info, t_keys *keys);
void	turn_left(t_info *info, t_keys *keys);
void	key_updapt2(t_info *info, t_keys *keys);
void	key_updapt(t_info *info, t_keys *keys);
void	key_updapt2(t_info *info, t_keys *keys);
void	look_up(t_info *info, t_keys *keys);
void	look_down(t_info *info, t_keys *keys);
void	jump(t_info *info);
void	crouch(t_info *info);

int		click_r(int b, int x, int y, t_info *info);
int		click(int b, int x, int y, t_info *info);
int		mouse_move(int x, int y, t_info *p);
void	ft_movement(t_info *info);

int		ft_key_press(int key_num, t_keys *keys);
int		ft_key_release(int key_num, t_keys *keys);
int		ft_click_exit(int keys, t_info *info);

void	save_bmp(t_info *info);
void	init_keys(t_keys *keys, t_info *info);
void	init_arr(t_info *info);
int		**alloc_arr(t_info *info);
int		**alloc_mini(t_info *info);
void	start_dir(t_info *info, char c, int x, int y);
void	arg_protect(t_info *info, int argc, char **argv);
int		open_mapfile(t_info *info, char *mapfile);
void	get_file(t_info *info);
void	tex_data(t_info *p, char *xpm_p, int n);
void	col_or_xpm(t_info *info, char *d, int n);
void	parse_map(t_info *info);
void	check_one_x(char **map, int i, int j, t_info *info);

void	calc_floor(t_info *info, t_floor *floor, int y);
void	calc_wall(t_info *info, int x);
void	diff_wall_floor(t_wall *wall);
void	fc_draw(t_wall *wall, t_info *info, int x);
void	calc_sprite(t_info *info);
void	put_in_wallbuf(t_wall *wall, t_info *info, int x);
void	sort_sprite(t_info *info, int *obj, double *dist, int amount);
void	put_in_spritebuf(t_sprite *sprite, t_info *info, int tex);
double	odd_sp(t_sprite *sprite);
double	even_sp(t_sprite *sprite);

void	sp_data(t_info *info, char **data);
void	count_item(char sp, t_info *info);
void	sp_get_offset(t_info *info, int i, int j, int *k);
void	load_image(t_info *info, int n, char *path, t_img *img);

void	floor_shadow(t_wall *wall, t_info *info, int x, int y);
void	ceiling_shadow(t_wall *wall, t_info *info, int x, int y);
void	wall_shadow(t_info *info, t_wall *wall, int y);
void	sprite_shadow(t_info *info, t_sprite *sprite);

void	pop_up(t_info *info);
void	rend_minimap(t_info *info);
void	next_stage(t_info *info, char *stage);
void	tex_buf(t_info *info);
void	tex_wh(t_info *info, int n, t_img *i);
void	show_yorn(t_info *info, t_img *img, char *path);
void	get_sp(t_info *info, char **data);
void	remove_item(t_info *info, int i);

void	weapon(t_info *p);
int		click(int b, int x, int y, t_info *info);
int		click_r(int b, int x, int y, t_info *info);
void	put_in_weapon(t_info *info, t_img *img, int n);
void	attack(t_info *info, t_img *img, char *path);
int		attack_sp(t_info *info, t_sprite *s, int tex);
void	put_in_spritebuf(t_sprite *s, t_info *info, int tex);
void	sp_or_dam(t_info *info, t_sprite *s, t_s *mob, int tex);
void	speed_up(t_info *info, t_keys *keys);
void	death_sound(t_info *info, int tex);
void	hit_sound(t_info *info, int tex, t_s *mob);
void	stage_sound(t_info *info);
void	rifle_sound(t_info *info);

void	sp_damaged(t_info *info, int i);
void	sp_slow(t_info *info, int i);
void	set_slow(t_info *info);
#endif
