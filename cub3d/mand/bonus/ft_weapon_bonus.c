/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_weapon_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:07:39 by junghan           #+#    #+#             */
/*   Updated: 2021/04/02 02:07:41 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_in_weapon(t_info *info, t_img *img, int n)
{
	int		y;
	int		x;
	int		z;
	int		w;

	z = 0;
	y = info->win_hei - img->img_height;
	while (y < info->win_hei)
	{
		y = info->win_hei - img->img_height + z;
		w = 0;
		x = info->win_wid - img->img_width;
		while (x < info->win_wid && z < img->img_height && w < img->img_width)
		{
			x = info->win_wid - img->img_width + w;
			if (info->texture[n][img->img_width * z + w] != -16777216)
				info->buf[y][x] = info->texture[n][img->img_width * z + w];
			w++;
		}
		z++;
	}
	free(info->texture[n]);
	info->texture[n] = 0;
}

void	put_in_cross(t_info *info, t_img *img, int n)
{
	int		y;
	int		x;
	int		z;
	int		w;

	z = 0;
	y = info->win_hei * 6 / 10 - (img->img_height / 2);
	while (y < info->win_hei * 6 / 10 + (img->img_height / 2))
	{
		y = info->win_hei * 6 / 10 - (img->img_height / 2) + z;
		w = 0;
		x = info->win_wid / 2 - (img->img_width / 2);
		while (x < info->win_wid / 2 + (img->img_width / 2) &&
				z < img->img_height && w < img->img_width)
		{
			x = info->win_wid / 2 - (img->img_width / 2) + w;
			if (info->texture[n][img->img_width * z + w] != -16777216)
				info->buf[y][x] = info->texture[n][img->img_width * z + w];
			w++;
		}
		z++;
	}
	free(info->texture[n]);
	info->texture[n] = 0;
}

void	show_cross(t_info *info, t_img *img, char *path)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(info->mlx,
			path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian);
	tex_wh(info, 17, img);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			info->texture[17][img->img_width * y + x] =
				img->data[img->img_width * y + x];
	}
	mlx_destroy_image(info->mlx, img->img);
	put_in_cross(info, img, 17);
}

void	show_weapon(t_info *info, t_img *img, char *path)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(info->mlx,
			path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian);
	tex_wh(info, 17, img);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			info->texture[17][img->img_width * y + x] =
				img->data[img->img_width * y + x];
	}
	mlx_destroy_image(info->mlx, img->img);
	put_in_weapon(info, img, 17);
}

void	weapon(t_info *info)
{
	t_img	i;

	show_cross(info, &i, "../textures/crosshair.xpm");
	if (info->skill_t == 0)
		show_weapon(info, &i, info->dis_wp);
	if (info->keys.key_p == 1 && info->skill1 == 1 && info->bullet == 0)
	{
		system("afplay ../sound/nobul.wav &");
		info->skill1 = 0;
	}
	if (info->skill1 == 1 && info->keys.key_p == 1 && info->bullet == 1)
		attack(info, &i, "../textures/riflehud2.xpm");
}
