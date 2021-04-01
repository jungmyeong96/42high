/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_utill2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:24:49 by junghan           #+#    #+#             */
/*   Updated: 2021/04/02 00:06:47 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	screen_size(t_info *info, char *w, char *h)
{
	int	wh[2];

	if (w == 0 || h == 0)
		error_exit("[ERROR] width or height empty!");
	if (ft_only_digit(w) == 0 || ft_only_digit(h) == 0)
		error_exit("[ERROR] width or height not digit!");
	info->win_wid = ft_atoi(w);
	info->win_hei = ft_atoi(h);
	mlx_get_screen_size(info->mlx, &wh[0], &wh[1]);
	if (info->win_wid > wh[0])
		info->win_wid = wh[0];
	if (info->win_hei > wh[1])
		info->win_hei = wh[1];
	if (info->win_wid < 640)
		info->win_wid = 640;
	if (info->win_hei < 480)
		info->win_hei = 480;
	if (info->win_wid == 0 || info->win_hei == 0)
		error_exit("[ERROR] screen size fail");
}

double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
