/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:02:59 by junghan           #+#    #+#             */
/*   Updated: 2021/03/28 08:55:12 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			+ (int)info->pos_y - 3] == '2')
		info->minimap[j][i] = 0x1FFF11;
	else if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '3')
		info->minimap[j][i] = 0x11F1F1;
	else if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '4')
		info->minimap[j][i] = 0x1F1011;
	else if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '5')
		info->minimap[j][i] = 0xF00011;
	else if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '6')
		info->minimap[j][i] = 0xB23BB1;
	else if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '7')
		info->minimap[j][i] = 0x39AAA1;
	else if (info->map[j / (int)((info->win_hei / 5) / 7)
			+ (int)info->pos_x - 3][i / (int)((info->win_wid / 4) / 7)
			+ (int)info->pos_y - 3] == '8')
		info->minimap[j][i] = 0x924477;
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
				info->minimap[j][i] = 0xFF0000;
			else if (info->map[(j / ((info->win_hei / 5) / 7)
						+ (int)info->pos_x) - 3][i / (int)((info->win_wid / 4) / 7)
					+ (int)info->pos_y - 3] == '0')
				info->minimap[j][i] = 0x111111 + info->buf[j]
					[i + (int)(info->win_wid * 3 / 4)];
			else
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
