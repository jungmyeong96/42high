/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_update3_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:04:44 by junghan           #+#    #+#             */
/*   Updated: 2021/04/02 02:04:47 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	look_up(t_info *info, t_keys *keys)
{
	info->pitch += 400 * keys->move_speed;
	if (info->pitch > info->win_hei * 2 / 5)
		info->pitch = info->win_hei * 2 / 5;
}

void	look_down(t_info *info, t_keys *keys)
{
	info->pitch -= 400 * keys->move_speed;
	if (info->pitch < -(info->win_hei * 2 / 5))
		info->pitch = -(info->win_hei * 2 / 5);
}

void	jump(t_info *info)
{
	if (info->pos_z == 0)
		system("afplay ../sound/jump.wav &");
	info->pos_z = 200;
}

void	crouch(t_info *info)
{
	if (info->pos_z == 0)
		system("afplay ../sound/crouch.wav &");
	info->pos_z = -150;
}
