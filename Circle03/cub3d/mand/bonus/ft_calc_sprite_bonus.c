/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_sprite_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:01:47 by junghan           #+#    #+#             */
/*   Updated: 2021/04/03 09:40:53 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_sprite_draw_p(t_sprite *sprite, t_info *info, t_s *mob, int tex)
{
	sprite->sprite_hei = abs((int)(info->win_hei / sprite->transf_y))
		/ VDIV;
	sprite->drawstart_y = -(sprite->sprite_hei) / 2 + info->win_hei
		/ 2 + sprite->vmove_scr;
	if (sprite->drawstart_y < 0)
		sprite->drawstart_y = 0;
	sprite->drawend_y = sprite->sprite_hei / 2 + info->win_hei
		/ 2 + sprite->vmove_scr;
	if (sprite->drawend_y >= info->win_hei)
		sprite->drawend_y = info->win_hei - 1;
	sprite->sprite_wid = abs((int)(info->win_hei / sprite->transf_y))
		/ UDIV;
	sprite->drawstart_x = -(sprite->sprite_wid) / 2 + sprite->sprite_scr_x;
	if (sprite->drawstart_x < 0)
		sprite->drawstart_x = 0;
	sprite->drawend_x = sprite->sprite_wid / 2 + sprite->sprite_scr_x;
	if (sprite->drawend_x >= info->win_wid)
		sprite->drawend_x = info->win_wid - 1;
	sp_or_dam(info, sprite, mob, tex);
}

double	sp_animate(t_info *info, t_sprite *sprite, int i)
{
	if ((info->sprite_arr[sprite->sprite_ord[i]].tex == 14
		&& info->stage_end == 2) ||
		(info->sprite_arr[sprite->sprite_ord[i]].tex == 15
		&& info->stage_end == 2) ||
		(info->sprite_arr[sprite->sprite_ord[i]].tex == 15
		&& info->stage_end == 1) ||
		(info->sprite_arr[sprite->sprite_ord[i]].tex >= 11 &&
		info->sprite_arr[sprite->sprite_ord[i]].tex <= 13) ||
		info->sprite_arr[sprite->sprite_ord[i]].tex >= 16)
	{
		if ((int)info->sprite_arr[sprite->sprite_ord[i]].x % 2 == 0)
			return (even_sp(sprite));
		else
			return (odd_sp(sprite));
	}
	else
		return (0.0);
}

void	set_sprite_info(t_sprite *sprite, t_info *info, int i)
{
	double sp_move;

	sp_move = sp_animate(info, sprite, i);
	sprite->sprite_x = info->sprite_arr[sprite->sprite_ord[i]].x
		- info->pos_x;
	sprite->sprite_y = info->sprite_arr[sprite->sprite_ord[i]].y
		- info->pos_y;
	sprite->invdet = 1.0 / (info->plane_x * info->dir_y - info->dir_x
			* info->plane_y);
	sprite->transf_x = sprite->invdet * (info->dir_y * sprite->sprite_x
			- info->dir_x * sprite->sprite_y);
	sprite->transf_y = sprite->invdet * (-(info->plane_y)
			* sprite->sprite_x + info->plane_x * sprite->sprite_y);
	sprite->sprite_scr_x = (int)((info->win_wid / 2)
			* (1 + sprite->transf_x / sprite->transf_y));
	sprite->vmove_scr = (int)(sp_move / sprite->transf_y) + info->pitch
		+ info->pos_z / sprite->transf_y;
	sprite->one_mob = sprite->sprite_ord[i];
	set_sprite_draw_p(sprite, info, &info->sprite_arr[sprite->sprite_ord[i]],
			info->sprite_arr[sprite->sprite_ord[i]].tex);
}

void	make_sprite_arr(t_sprite *sprite, t_info *info)
{
	int i;

	i = 0;
	while (i < info->sp_count)
	{
		remove_item(info, i);
		sprite->sprite_ord[i] = i;
		sprite->sprite_dist[i] = ((info->pos_x - info->sprite_arr[i].x)
				* (info->pos_x - info->sprite_arr[i].x)
				+ (info->pos_y - info->sprite_arr[i].y)
				* (info->pos_y - info->sprite_arr[i].y));
		i++;
	}
	sort_sprite(info, sprite->sprite_ord,
			sprite->sprite_dist, info->sp_count);
}

void	calc_sprite(t_info *info)
{
	int i;

	if (!(info->sprite.sprite_ord = (int *)ft_calloc(info->sp_count,
					sizeof(int))))
		error_exit("Error: sprite_ord allocation fail!\n");
	if (!(info->sprite.sprite_dist = (double *)ft_calloc(info->sp_count,
					sizeof(double))))
		error_exit("Error: sprite_dist allocation fail!\n");
	make_sprite_arr(&info->sprite, info);
	i = 0;
	info->slow_t++;
	info->damaged_t++;
	while (i < info->sp_count)
	{
		set_sprite_info(&info->sprite, info, i);
		if (info->slow != 1)
			sp_slow(info, i);
		sp_damaged(info, i);
		i++;
	}
	free(info->sprite.sprite_ord);
	free(info->sprite.sprite_dist);
}
