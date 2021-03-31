/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stimpack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:59:05 by junghan           #+#    #+#             */
/*   Updated: 2021/03/30 21:18:45 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_in_stimpack(t_info *info, t_img *img)
{
	int	y;
	int	x;
	int	z;

	z = 0;
	y = 0;
	while (y < 100 + img->img_height)
	{
		y = 100 + z;
		x = 0;
		while (x < img->img_width && z < img->img_height)
		{
			if (info->texture[18][img->img_width * z + x] != -16777216)
				info->buf[y][x] = info->texture[18][img->img_width * z + x];
			x++;
		}
		z++;
	}
	free(info->texture[18]);
}

void	stimpack(t_info *info, t_img *img, char *path)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(info->mlx,
			path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian);
	tex_wh(info, 18, img);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			info->texture[18][img->img_width * y + x] =
				img->data[img->img_width * y + x];
	}
	mlx_destroy_image(info->mlx, img->img);
	put_in_stimpack(info, img);
}

void	speed_up(t_info *info, t_keys *keys)
{
	t_img imgg;

	if (keys->key_e && keys->health != 1 && keys->stim_time == 0
			&& info->slow == 0)
	{
		system("afplay ../sound/stimpack.wav &");
		keys->health--;
		keys->move_speed = 0.1;
		keys->rot_speed = 0.1;
		info->stim_switch = 1;
	}
	if (keys->stim_time == 0)
		stimpack(info, &imgg, "../textures/stimpack.xpm");//hp0일 때 까망:ㅈ
	if (info->stim_switch && keys->stim_time < 100)
	{
		keys->stim_time++;
		if (keys->stim_time == 100)
		{
			keys->stim_time = 0;
			info->stim_switch = 0;
			keys->move_speed = 0.05;
			keys->rot_speed = 0.05;
		}
	}
}
