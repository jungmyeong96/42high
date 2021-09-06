/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:00:04 by junghan           #+#    #+#             */
/*   Updated: 2021/04/02 02:00:08 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		**alloc_mini(t_info *info)
{
	int i;

	if (!(info->minimap = (int **)ft_calloc((int)(info->win_hei
		/ 5), sizeof(int *))))
		error_exit("some error in malloc");
	i = 0;
	while (i < info->win_hei / 5)
	{
		if (!(info->minimap[i] = (int *)ft_calloc((int)(info->win_wid
						/ 4), sizeof(int))))
			error_exit("some error in mallc");
		i++;
	}
	return (0);
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
