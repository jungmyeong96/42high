/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_utill2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:02:58 by junghan           #+#    #+#             */
/*   Updated: 2021/04/03 10:11:03 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	screen_size(t_info *info, char *w, char *h)
{
	int	wh[2];

	if (w == 0 || h == 0)
		error_exit("Error: width or height empty!");
	if (ft_only_digit(w) == 0 || ft_only_digit(h) == 0)
		error_exit("Error: width or height not digit!");
	info->win_wid = ft_atoi(w);
	info->win_hei = ft_atoi(h);
	mlx_get_screen_size(info->mlx, &wh[0], &wh[1]);
	if (info->win_wid > wh[0])
		info->win_wid = wh[0];
	if (info->win_hei > wh[1])
		info->win_hei = wh[1];
	if (info->win_wid < 768)
		info->win_wid = 768;
	if (info->win_hei < 768)
		info->win_hei = 768;
	if (info->win_wid != 768 || info->win_hei != 768)
		write(1, "recommend 768 768", 18);
	if (info->win_wid == 0 || info->win_hei == 0)
		error_exit("Error: screen size fail");
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
