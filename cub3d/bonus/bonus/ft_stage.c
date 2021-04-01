/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 06:42:35 by junghan           #+#    #+#             */
/*   Updated: 2021/03/30 21:03:40 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rebase(t_info *info)
{
	int		i;

	i = -1;
	while (++i < 7)
		info->check_ele[i] = 0;
	free_dou(info->map);
	init_arr(info);
	init_keys(&info->keys, info);
}

void	next_stage(t_info *info, char *stage)
{
	stage_sound(info);
	if (info->level_up == 1)
		info->stage_end++;
	if (info->stage_end == 3)
		info->stage_end = 0;
	rebase(info);
	open_mapfile(info, stage);
	get_file(info);
	parse_map(info);
	info->img.img = mlx_new_image(info->mlx, info->win_wid, info->win_hei);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp,
			&info->img.size_l, &info->img.endian);
}
