/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:01:11 by junghan           #+#    #+#             */
/*   Updated: 2021/10/11 11:01:13 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	get_texture5(t_info *info)
{
	info->tex[12].addr = (unsigned int *)mlx_get_data_addr(info->tex[12].img, \
	&info->tex[12].bits_per_pixel, &info->tex[12].line_length, \
	&info->tex[12].endian);
	info->tex[13].addr = (unsigned int *)mlx_get_data_addr(info->tex[13].img, \
	&info->tex[13].bits_per_pixel, &info->tex[13].line_length, \
	&info->tex[13].endian);
	info->tex[14].addr = (unsigned int *)mlx_get_data_addr(info->tex[14].img, \
	&info->tex[14].bits_per_pixel, &info->tex[14].line_length, \
	&info->tex[14].endian);
	info->tex[15].addr = (unsigned int *)mlx_get_data_addr(info->tex[15].img, \
	&info->tex[15].bits_per_pixel, &info->tex[15].line_length, \
	&info->tex[15].endian);
	info->tex[16].addr = (unsigned int *)mlx_get_data_addr(info->tex[16].img, \
	&info->tex[16].bits_per_pixel, &info->tex[16].line_length, \
	&info->tex[16].endian);
	info->tex[17].addr = (unsigned int *)mlx_get_data_addr(info->tex[17].img, \
	&info->tex[17].bits_per_pixel, &info->tex[17].line_length, \
	&info->tex[17].endian);
	info->tex[18].addr = (unsigned int *)mlx_get_data_addr(info->tex[18].img, \
	&info->tex[18].bits_per_pixel, &info->tex[18].line_length, \
	&info->tex[18].endian);
}

void	get_texture4(t_info *info)
{
	info->tex[6].addr = (unsigned int *)mlx_get_data_addr(info->tex[6].img, \
	&info->tex[6].bits_per_pixel, &info->tex[6].line_length, \
	&info->tex[6].endian);
	info->tex[7].addr = (unsigned int *)mlx_get_data_addr(info->tex[7].img, \
	&info->tex[7].bits_per_pixel, &info->tex[7].line_length, \
	&info->tex[7].endian);
	info->tex[8].addr = (unsigned int *)mlx_get_data_addr(info->tex[8].img, \
	&info->tex[8].bits_per_pixel, &info->tex[8].line_length, \
	&info->tex[8].endian);
	info->tex[9].addr = (unsigned int *)mlx_get_data_addr(info->tex[9].img, \
	&info->tex[9].bits_per_pixel, &info->tex[9].line_length, \
	&info->tex[9].endian);
	info->tex[10].addr = (unsigned int *)mlx_get_data_addr(info->tex[10].img, \
	&info->tex[10].bits_per_pixel, &info->tex[10].line_length, \
	&info->tex[10].endian);
	info->tex[11].addr = (unsigned int *)mlx_get_data_addr(info->tex[11].img, \
	&info->tex[11].bits_per_pixel, &info->tex[11].line_length, \
	&info->tex[11].endian);
	get_texture5(info);
}

void	get_texture3(t_info *info)
{
	info->tex[0].addr = (unsigned int *)mlx_get_data_addr(info->tex[0].img, \
	&info->tex[0].bits_per_pixel, &info->tex[0].line_length, \
	&info->tex[0].endian);
	info->tex[1].addr = (unsigned int *)mlx_get_data_addr(info->tex[1].img, \
	&info->tex[1].bits_per_pixel, &info->tex[1].line_length, \
	&info->tex[1].endian);
	info->tex[2].addr = (unsigned int *)mlx_get_data_addr(info->tex[2].img, \
	&info->tex[2].bits_per_pixel, &info->tex[2].line_length, \
	&info->tex[2].endian);
	info->tex[3].addr = (unsigned int *)mlx_get_data_addr(info->tex[3].img, \
	&info->tex[3].bits_per_pixel, &info->tex[3].line_length, \
	&info->tex[3].endian);
	info->tex[4].addr = (unsigned int *)mlx_get_data_addr(info->tex[4].img, \
	&info->tex[4].bits_per_pixel, &info->tex[4].line_length, \
	&info->tex[4].endian);
	info->tex[5].addr = (unsigned int *)mlx_get_data_addr(info->tex[5].img, \
	&info->tex[5].bits_per_pixel, &info->tex[5].line_length, \
	&info->tex[5].endian);
	get_texture4(info);
}

void	get_texture2(t_info *info)
{
	info->tex[9].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/ilnl.xpm", &info->tex[9].img_width, &info->tex[9].img_height);
	info->tex[10].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/ilnl2.xpm", &info->tex[10].img_width, &info->tex[10].img_height);
	info->tex[11].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/ilnb.xpm", &info->tex[11].img_width, &info->tex[11].img_height);
	info->tex[12].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/ilnb2.xpm", &info->tex[12].img_width, &info->tex[12].img_height);
	info->tex[13].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/ilnf.xpm", &info->tex[13].img_width, &info->tex[13].img_height);
	info->tex[14].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/ilnf2.xpm", &info->tex[14].img_width, &info->tex[14].img_height);
	info->tex[15].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/cir1.xpm", &info->tex[15].img_width, &info->tex[15].img_height);
	info->tex[16].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/cir2.xpm", &info->tex[16].img_width, &info->tex[16].img_height);
	info->tex[17].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/cil1.xpm", &info->tex[17].img_width, &info->tex[17].img_height);
	info->tex[18].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/cil2.xpm", &info->tex[18].img_width, &info->tex[18].img_height);
	get_texture3(info);
}

void	get_texture(t_info *info)
{
	info->tex[0].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/ozing.xpm", &info->tex[0].img_width, &info->tex[0].img_height);
	info->tex[1].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/ozing2.xpm", &info->tex[1].img_width, &info->tex[1].img_height);
	info->tex[2].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/dalgo.xpm", &info->tex[2].img_width, &info->tex[2].img_height);
	info->tex[3].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/dalgo3.xpm", &info->tex[3].img_width, &info->tex[3].img_height);
	info->tex[4].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/dalgo2.xpm", &info->tex[4].img_width, &info->tex[4].img_height);
	info->tex[5].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/dalgo.xpm", &info->tex[5].img_width, &info->tex[5].img_height);
	info->tex[6].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/exit_p.xpm", &info->tex[6].img_width, &info->tex[6].img_height);
	info->tex[7].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/ilnr.xpm", &info->tex[7].img_width, &info->tex[7].img_height);
	info->tex[8].img = mlx_xpm_file_to_image(info->win.mlx, \
	"./texture/ilnr2.xpm", &info->tex[8].img_width, &info->tex[8].img_height);
	get_texture2(info);
}
