/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pick_item.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 23:55:24 by junghan           #+#    #+#             */
/*   Updated: 2021/03/30 03:56:46 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		pick_item(t_info *info, char item)
{
	if (item == '3')
	{
		system("afplay ../sound/getgun.wav &");
		info->weapon = 1;
	}
	if (item == '4')
	{
		system("afplay ../sound/heal.wav &");
		info->keys.health += 3;
		if (info->keys.health > 5)
			info->keys.health = 5;
	}
	if (item == '5')
	{
		system("afplay ../sound/reload.wav &");
		info->bullet = 1;
	}
}

void	remove_item(t_info *info, int i)
{
	if (info->map[(int)info->pos_x][(int)info->pos_y] == '3' ||
		info->map[(int)info->pos_x][(int)info->pos_y] == '4' ||
		info->map[(int)info->pos_x][(int)info->pos_y] == '5' ||
		info->map[(int)info->pos_x][(int)info->pos_y] == '8')
		if ((int)info->sprite_arr[i].x == (int)info->pos_x &&
				(int)info->sprite_arr[i].y == (int)info->pos_y)
		{
			pick_item(info, info->map[(int)info->pos_x][(int)info->pos_y]);
			info->sprite_arr[i].x = 0;
			info->sprite_arr[i].y = 0;
			info->sprite_arr[i].tex = 0;
			info->map[(int)info->pos_x][(int)info->pos_y] = '0';
		}
}
