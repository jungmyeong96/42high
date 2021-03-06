/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_n_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:09:50 by junghan           #+#    #+#             */
/*   Updated: 2021/05/16 19:23:49 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_dir2(t_info *info, char c)
{
	if (c == 'N')
	{
		info->dir_x = -1 ;// + 0.000001);
		info->dir_y =  0;//0.000001;
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
}

void	init_keys(t_keys *keys)
{
	keys->key_a = 0;
	keys->key_w = 0;
	keys->key_s = 0;
	keys->key_d = 0;
	keys->key_left = 0;
	keys->key_right = 0;
	keys->key_esc = 0;
	keys->move_speed = 0.05;
	keys->rot_speed = 0.05;
}

int		**alloc_arr(t_info *info)
{
	int	i;

	if (!(info->buf = (int **)ft_calloc(info->win_hei, sizeof(int *))))
		error_exit("some error in malloc");
	if (!(info->z_buffer = (double *)ft_calloc(info->win_wid, sizeof(double))))
		error_exit("some error in malloc");
	i = 0;
	while (i < info->win_hei)
	{
		if (!(info->buf[i] = (int *)ft_calloc(info->win_wid, sizeof(int))))
			error_exit("some error in mallc");
		i++;
	}
	return (0);
}
