/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:04:53 by junghan           #+#    #+#             */
/*   Updated: 2021/07/22 16:46:57 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	map_draw(t_info *info)
{
	int	y;
	int	x;

	y = -1;
	while (++y < info->win_hei)
	{
		x = -1;
		while (++x < info->win_wid)
		{
			info->img.data[y * info->win_wid + x] = info->buf[y][x];
			info->buf[y][x] = 0;
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	map_calc(t_info *info)
{
	int		x;
	t_img	img;

	x = 0;
	while (x < info->win_wid)
	{
		calc_wall(info, x);
		x++;
	}
	calc_sprite(info);
	pop_up(info);
	rend_minimap(info);
	if (info->level_up == 1)
	{
		if (info->stage_end == 2)
			show_yorn(info, &img, "../textures/missioncom.xpm");
		else
			show_yorn(info, &img, "../textures/next_stage.xpm");
		if (info->stage_sound == 1 && info->stage_t == 1)
			system("afplay ../sound/tankwall.wav &");
		if (info->keys.key_o == 1)
			next_stage(info, info->stage);
	}
}

int		main_loop(t_info *info)
{
	map_calc(info);
	map_draw(info);
	save_bmp(info);
	key_updapt(info, &info->keys);
	if (info->map[(int)info->pos_x][(int)info->pos_y] == '8')
		info->level_up = 1;
	return (0);
}

void	pre_game(t_info *info, int argc, char **argv)
{
	init_arr(info);
	arg_protect(info, argc, argv);
	open_mapfile(info, argv[1]);
	tex_buf(info);
	get_file(info);
	alloc_arr(info);
	alloc_mini(info);
	parse_map(info);
	system("afplay ../sound/terranbgm.wav &");
	info->stage_end = 0;
	system("afplay ../sound/tankwall.wav &");
	info->stage_t = 0;
	init_keys(&info->keys, info);
}

int		main(int argc, char **argv)
{
	t_info	info;

	info.mlx = mlx_init();
	pre_game(&info, argc, argv);
	info.win = mlx_new_window(info.mlx, info.win_wid, info.win_hei, "mlx");
	info.img.img = mlx_new_image(info.mlx, info.win_wid, info.win_hei);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp,
			&info.img.size_l, &info.img.endian);
	mlx_hook(info.win, 2, 0, &ft_key_press, &info.keys);
	mlx_hook(info.win, 3, 0, &ft_key_release, &info.keys);
	mlx_hook(info.win, 17, 0, &ft_click_exit, &info.keys);
	mlx_hook(info.win, 4, 0, click, &info);
	mlx_hook(info.win, 5, 0, click_r, &info);
	mlx_hook(info.win, 6, 0, &mouse_move, &info);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_loop(info.mlx);
	return (0);
}
