/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_texture_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:06:12 by junghan           #+#    #+#             */
/*   Updated: 2021/07/22 13:20:15 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_image(t_info *info, int n, char *path, t_img *img)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(info->mlx,
			path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian);
	tex_wh(info, n, img);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			info->texture[n][img->img_width * y + x] =
				img->data[img->img_width * y + x];
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	tex_data(t_info *info, char *xpm_p, int n)
{
	int		fd;

	if (xpm_p == 0 || ft_check_extation(xpm_p, ".xpm") == 0)
		error_exit("Error: no such path to xpm\n!");
	fd = open(xpm_p, O_RDONLY);
	if (fd == -1)
		error_exit("Error: no such xpm!\n");
	close(fd);
	load_image(info, n, xpm_p, &info->img);
}

void	color_check(t_info *info, int rgb, int n)
{
	info->fcrgb.c_rgb = 0;
	info->fcrgb.f_rgb = 0;
	if (n == 5)
	{
		info->fcrgb.f_rgb = 1;
		info->fcrgb.color_f = rgb;
	}
	else if (n == 6)
	{
		info->fcrgb.c_rgb = 1;
		info->fcrgb.color_c = rgb;
	}
}

void	fc_color(t_info *info, char *rgb_data, int n)
{
	char	**rgb;
	int		bin;
	int		temp;
	int		i;

	if (!(rgb = ft_split(rgb_data, ',')))
		error_exit("Error: rgb data fail!\n");
	i = 0;
	bin = 0;
	while (i < 3)
	{
		if (!rgb[i] || !ft_only_digit(rgb[i]))
			error_exit("Error: no such rgb data!\n");
		temp = ft_atoi(rgb[i]);
		if (temp > 255 || temp < 0)
			error_exit("Error: rgb range fail!\n");
		bin = bin * 256 + temp;
		i++;
	}
	color_check(info, bin, n);
	free_dou(rgb);
}

void	col_or_xpm(t_info *info, char *d, int n)
{
	if (ft_check_extation(d, ".xpm") != 1)
		fc_color(info, d, n);
	else if (ft_check_extation(d, ".xpm") == 1)
		tex_data(info, d, n);
}
