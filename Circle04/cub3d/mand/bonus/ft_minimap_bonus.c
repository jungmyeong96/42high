/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:05:12 by junghan           #+#    #+#             */
/*   Updated: 2021/04/02 02:05:15 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_pos(t_info *info, int j, int i)
{
	if (j >= 3 * ((info->win_hei / 5) / 7)
			&& j <= 4 * ((info->win_hei / 5) / 7))
		if (i >= 3 * ((info->win_wid / 4) / 7)
				&& i <= 4 * ((info->win_wid / 4) / 7))
			info->minimap[j][i] = 0xFD93F999;
}

void	add_mini_color(t_info *info, int j, int i)
{
	if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '3')
		info->minimap[j][i] = 0x336699;
	else if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '4')
		info->minimap[j][i] = 0x33FF00;
	else if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '5')
		info->minimap[j][i] = 0x66FFCC;
	else if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '6')
		info->minimap[j][i] = 0x660033;
	else if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '7')
		info->minimap[j][i] = 0xFF6699;
	else if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '8')
		info->minimap[j][i] = 0x9900FF;
}

void	wall_minimap(t_info *info, int j, int i)
{
	if ((j / (int)((info->win_hei / 5) / 7) + (int)info->pos_x >= 3) &&
			(int)(j / ((info->win_hei / 5) / 7) + info->pos_x - 3)
			< info->map_lines)
	{
		if (i / (int)((info->win_wid / 4) / 7) + (int)info->pos_y >= 3 &&
				(int)(i / ((info->win_wid / 4) / 7) + info->pos_y - 3)
				< (int)ft_strlen(info->map[(int)(j / ((info->win_hei / 5) / 7)
						+ info->pos_x - 3)]))
		{
			if (info->map[(int)(j / ((info->win_hei / 5) / 7)
						+ info->pos_x - 3)][(int)(i / ((info->win_wid / 4) / 7)
						+ info->pos_y - 3)] == '1')
				info->minimap[j][i] = 0xFFFF66;
			else if (info->map[(j / ((info->win_hei / 5) / 7)
					+ (int)info->pos_x) - 3][i / (int)((info->win_wid / 4) / 7)
					+ (int)info->pos_y - 3] == '0')
				info->minimap[j][i] = 0x111111 + info->buf[j]
					[i + (int)(info->win_wid * 3 / 4)];
			else if (info->map[j / (int)((info->win_hei / 5) / 7)
					+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
					+ (int)info->pos_y - 3] == '2')
				info->minimap[j][i] = 0xFF3333;
			add_mini_color(info, j, i);
		}
	}
}

void	map_background(t_info *info)
{
	int	i;
	int j;

	j = 0;
	while (j < info->win_hei / 5)
	{
		i = 0;
		while (i < info->win_wid / 4)
		{
			info->minimap[j][i] = 0x111111 + info->buf[j]
				[i + info->win_wid * 3 / 4];
			i++;
		}
		j++;
	}
	j = -1;
	while (++j < (int)(info->win_hei / 5))
	{
		i = -1;
		while (++i < (int)(info->win_wid / 4))
		{
			wall_minimap(info, j, i);
			get_pos(info, j, i);
		}
	}
}

void	rend_minimap(t_info *info)
{
	int	i;
	int j;
	int k;

	map_background(info);
	j = 0;
	while (j < info->win_hei / 5)
	{
		i = info->win_wid * 3 / 4;
		k = 0;
		while (i < info->win_wid && k < (int)(info->win_wid / 4))
		{
			info->buf[j][i] = info->minimap[j][k];
			info->minimap[j][k] = 0;
			k++;
			i++;
		}
		j++;
	}
}
