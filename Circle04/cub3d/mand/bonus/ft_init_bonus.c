/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:04:10 by junghan           #+#    #+#             */
/*   Updated: 2021/04/02 02:04:14 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	start_dir2(t_info *info, char c)
{
	if (c == 'N')
	{
		info->dir_x = -1;
		info->dir_y = 0;
		info->plane_x = 0;
		info->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		info->dir_x = 0;
		info->dir_y = -1;
		info->plane_x = -0.66;
		info->plane_y = 0;
	}
}

void	start_dir(t_info *info, char c, int x, int y)
{
	info->pos_x = x + 0.5;
	info->pos_y = y + 0.5;
	info->pitch = 0;
	if (c == 'E')
	{
		info->dir_x = 0;
		info->dir_y = 1;
		info->plane_x = 0.66;
		info->plane_y = 0;
	}
	else if (c == 'S')
	{
		info->dir_x = 1;
		info->dir_y = 0;
		info->plane_x = 0;
		info->plane_y = -0.66;
	}
	else
		start_dir2(info, c);
}

void	init_arr(t_info *info)
{
	info->sp_count = 0;
	info->is_save = 0;
	info->keys.yorn = 0;
	info->sp2 = 0;
	info->sp3 = 0;
	info->sp4 = 0;
	info->sp5 = 0;
	info->sp6 = 0;
	info->sp7 = 0;
	info->sp8 = 0;
	info->weapon = 0;
	info->skill1 = 0;
	info->skill2 = 0;
	info->stage_t = 0;
	info->stage_sound = 0;
	info->skill_t = 0;
	info->bullet = 0;
	info->sp_hit = 0;
	info->damaged_t = 0;
	info->damage = 0;
	info->slow_t = 0;
	info->slow = 0;
	info->level_up = 0;
	info->stim_switch = 0;
	info->sprite.save_mob = -1;
}

void	init_keys(t_keys *keys, t_info *info)
{
	keys->key_a = 0;
	keys->key_w = 0;
	keys->key_s = 0;
	keys->key_d = 0;
	keys->key_o = 0;
	keys->key_left = 0;
	keys->key_right = 0;
	keys->key_p = 0;
	keys->key_r = 0;
	keys->key_f = 0;
	keys->key_e = 0;
	keys->key_up = 0;
	keys->key_down = 0;
	keys->key_esc = 0;
	keys->hurt = 0;
	keys->health = 5;
	keys->stim_time = 0;
	keys->move_speed = 0.05;
	keys->rot_speed = 0.05;
	keys->zero_p = info->win_wid / 2;
	keys->zero_p2 = info->win_hei / 2;
	keys->move_p = 0;
	info->sprite.vmove = 0.0;
	info->sprite.vmove2 = 60.0;
	info->sprite.is_animate = 0;
}
