/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_damaged.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 05:31:42 by junghan           #+#    #+#             */
/*   Updated: 2021/04/01 23:50:02 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_slow(t_info *info)
{
	if (info->slow != 0)
	{
		if (info->slow_t == 1)
			system("afplay ../sound/slow.wav &");
		info->keys.move_speed = 0.02;
		if (info->slow_t > 50)
		{
			info->slow_t = 0;
			info->slow = 0;
		}
	}
	else if (info->slow == 0 && info->stim_switch == 0)
	{
		info->keys.move_speed = 0.05;
		info->slow_t = 0;
	}
}

void	sp_slow(t_info *info, int i)
{
	if (info->sprite_arr[i].tex == 14 && info->stage_end == 1)
	{
		if ((int)info->pos_x < (int)(info->sprite_arr[i].x + 2) &&
				(int)info->pos_x > (int)(info->sprite_arr[i].x - 2))
		{
			if (((int)info->pos_y < (int)info->sprite_arr[i].y + 2 &&
						(int)info->pos_y > (int)info->sprite_arr[i].y - 2))
				info->slow = 1;
		}
		else if (!(((int)info->pos_x < (int)(info->sprite_arr[i].x + 2) &&
				(int)info->pos_x > (int)(info->sprite_arr[i].x - 2)) &&
				((int)info->pos_y < (int)info->sprite_arr[i].y + 2 &&
				(int)info->pos_y > (int)info->sprite_arr[i].y - 2)))
			info->slow = 0;
	}
	if (info->slow_t > 1000)
		info->slow_t = 0;
}

void	sp_damaged(t_info *info, int i)
{
	if ((info->sprite_arr[i].tex == 10 || info->sprite_arr[i].tex == 15
				|| (info->sprite_arr[i].tex == 14 && info->stage_end == 2))
			&& info->damaged_t > 50)
	{
		if ((int)info->pos_x < (int)(info->sprite_arr[i].x + 2) &&
				(int)info->pos_x > (int)(info->sprite_arr[i].x - 2))
		{
			if (((int)info->pos_y < (int)info->sprite_arr[i].y + 2 &&
						(int)info->pos_y > (int)info->sprite_arr[i].y - 2))
			{
				info->damage = 1;
				info->damaged_t = 0;
			}
		}
	}
	if (info->damaged_t > 1000)
		info->damaged_t = 0;
}
