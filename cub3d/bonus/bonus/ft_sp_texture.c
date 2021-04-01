/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sp_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 23:32:06 by junghan           #+#    #+#             */
/*   Updated: 2021/04/01 23:14:11 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sp_get_offset3(t_info *info, int i, int j, int *k)
{
	if (info->map[i][j] == '8')
	{
		info->sprite_arr[*k].x = i + 0.5;
		info->sprite_arr[*k].y = j + 0.5;
		info->sprite_arr[(*k)++].tex = 16;
	}
}

void	sp_get_offset2(t_info *info, int i, int j, int *k)
{
	if (info->map[i][j] == '5')
	{
		info->sprite_arr[*k].x = i + 0.5;
		info->sprite_arr[*k].y = j + 0.5;
		info->sprite_arr[(*k)++].tex = 13;
	}
	else if (info->map[i][j] == '6')
	{
		info->sprite_arr[*k].x = i + 0.5;
		info->sprite_arr[*k].y = j + 0.5;
		info->sprite_arr[*k].tex = 15;
		info->sprite_arr[(*k)++].hit = 0;
	}
	else if (info->map[i][j] == '7')
	{
		info->sprite_arr[*k].x = i + 0.5;
		info->sprite_arr[*k].y = j + 0.5;
		info->sprite_arr[*k].tex = 14;
		info->sprite_arr[(*k)++].hit = 0;
	}
	sp_get_offset3(info, i, j, k);
}

void	sp_get_offset(t_info *info, int i, int j, int *k)
{
	if (info->map[i][j] == '2')
	{
		info->sprite_arr[*k].x = i + 0.5;
		info->sprite_arr[*k].y = j + 0.5;
		info->sprite_arr[*k].tex = 10;
		info->sprite_arr[(*k)++].hit = 0;
	}
	else if (info->map[i][j] == '3')
	{
		info->sprite_arr[*k].x = i + 0.5;
		info->sprite_arr[*k].y = j + 0.5;
		info->sprite_arr[(*k)++].tex = 11;
	}
	else if (info->map[i][j] == '4')
	{
		info->sprite_arr[*k].x = i + 0.5;
		info->sprite_arr[*k].y = j + 0.5;
		info->sprite_arr[(*k)++].tex = 12;
	}
	sp_get_offset2(info, i, j, k);
}

void	count_item(char sp, t_info *info)
{
	if (sp == '2')
		info->sp2++;
	else if (sp == '3')
		info->sp3++;
	else if (sp == '4')
		info->sp4++;
	else if (sp == '5')
		info->sp5++;
	else if (sp == '6')
		info->sp6++;
	else if (sp == '7')
		info->sp7++;
	else if (sp == '8')
		info->sp8++;
}

void	sp_data(t_info *info, char **data)
{
	int		fd;
	int		n;

	n = 1;
	while (n < 9)
	{
		if (data == 0 || ft_check_extation(data[n], ".xpm") == 0)
			error_exit("[ERROR] no such path to xpm\n!");
		fd = open(data[n], O_RDONLY);
		if (fd == -1)
			error_exit("[ERROR] no such xpm!\n");
		close(fd);
		if (n == 8)
			info->dis_wp = ft_strdup(data[n]);
		load_image(info, n + 9, data[n], &info->img);
		n++;
	}
}
