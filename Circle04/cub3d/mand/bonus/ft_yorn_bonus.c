/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_yorn_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:07:52 by junghan           #+#    #+#             */
/*   Updated: 2021/04/02 02:08:00 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_key_sound(t_info *info, int n, char *path)
{
	if (info->level_up == 1)
	{
		info->stage_sound = 1;
		if (info->stage_t > 500)
			info->stage_t = 0;
	}
	else if (info->keys.health == 0)
	{
		info->stage_sound = 1;
		if (info->stage_t > 500)
			info->stage_t = 0;
	}
	if (info->stage_t > 1000)
		info->stage_t = 0;
	if (info->keys.key_o == 1)
		next_stage(info, path);
	free(info->texture[n]);
}

void	put_yorn(t_info *info, t_img *i, int n, char *path)
{
	int	y;
	int	x;
	int z;
	int w;

	z = 0;
	y = (info->win_hei / 2) - (i->img_height / 2);
	info->keys.yorn = 1;
	while (++y < (info->win_hei / 2) + (i->img_height / 2))
	{
		w = 0;
		y = (info->win_hei / 2) - (i->img_height / 2) + z;
		x = (info->win_wid / 2) - (i->img_width / 2);
		while (++x < (info->win_wid / 2) + (i->img_width / 2) &&
				z < i->img_height && w < i->img_width)
		{
			x = (info->win_wid / 2) - (i->img_width / 2) + w;
			if (info->texture[n][i->img_width * z + w] != -16777216)
				info->buf[y][x] = info->texture[n][i->img_width * z + w];
			w++;
		}
		z++;
	}
	info->stage_t++;
	check_key_sound(info, n, path);
}

void	check_yorn(t_info *info, t_img *img)
{
	if (info->keys.health <= 0)
		put_yorn(info, img, 8, "terran.cub");
	else if (info->level_up == 1)
		put_yorn(info, img, 8, info->stage);
}

void	show_yorn(t_info *info, t_img *img, char *path)
{
	int		x;
	int		y;

	img->img = 0;
	img->bpp = 0;
	img->size_l = 0;
	img->endian = 0;
	if (!(img->img = mlx_xpm_file_to_image(info->mlx,
			path, &img->img_width, &img->img_height)))
		return ;
	if (!(img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian)))
		return ;
	tex_wh(info, 8, img);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			info->texture[8][img->img_width * y + x] =
				img->data[img->img_width * y + x];
	}
	mlx_destroy_image(info->mlx, img->img);
	check_yorn(info, img);
}
