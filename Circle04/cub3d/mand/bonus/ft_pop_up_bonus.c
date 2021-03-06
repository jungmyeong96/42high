/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_up_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:05:57 by junghan           #+#    #+#             */
/*   Updated: 2021/04/02 02:05:59 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_in_buf(t_info *info, t_img *img)
{
	int	y;
	int	x;
	int	z;

	z = 0;
	y = 0;
	while (y < img->img_height + info->win_hei / 2)
	{
		y = info->win_hei * 0.02 + z;
		x = 0;
		while (x < img->img_width && z < img->img_height)
		{
			if (info->texture[7][img->img_width * z + x] != -16777216)
				info->buf[y][x] = info->texture[7][img->img_width * z + x];
			x++;
		}
		z++;
	}
	free(info->texture[7]);
}

void	show_hp(t_info *info, t_img *img, char *path)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(info->mlx,
			path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian);
	tex_wh(info, 7, img);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			info->texture[7][img->img_width * y + x] =
				img->data[img->img_width * y + x];
	}
	mlx_destroy_image(info->mlx, img->img);
	put_in_buf(info, img);
	if (info->keys.health <= 0)
	{
		info->stage_end = 0;
		show_yorn(info, img, "../textures/game_over_m2.xpm");
		if (info->stage_sound == 1 && info->stage_t == 1)
			system("afplay ../sound/gameover.wav &");
	}
}

void	check_hurt(t_info *info, t_keys *keys)
{
	t_img imgg;

	set_slow(info);
	if (keys->hurt || info->damage)
	{
		keys->health--;
		system("afplay ../sound/mahurt.wav &");
		keys->hurt = 0;
		info->damage = 0;
	}
	if (keys->health == 5)
		show_hp(info, &imgg, "../textures/hp5.xpm");
	else if (keys->health == 4)
		show_hp(info, &imgg, "../textures/hp4.xpm");
	else if (keys->health == 3)
		show_hp(info, &imgg, "../textures/hp3.xpm");
	else if (keys->health == 2)
		show_hp(info, &imgg, "../textures/hp2.xpm");
	else if (keys->health == 1)
		show_hp(info, &imgg, "../textures/hp1.xpm");
	else if (keys->health <= 0)
		show_hp(info, &imgg, "../textures/hp0.xpm");
}

void	pop_up(t_info *info)
{
	check_hurt(info, &info->keys);
	speed_up(info, &info->keys);
	if (info->weapon == 1)
		weapon(info);
}
