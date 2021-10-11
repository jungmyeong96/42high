/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:02:06 by junghan           #+#    #+#             */
/*   Updated: 2021/10/11 11:02:08 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_exit(t_info *info)
{
	int		x;

	mlx_destroy_window(info->win.mlx, info->win.mlx_win);
	mlx_destroy_image(info->win.mlx, info->fimg.img);
	x = -1;
	while (++x < 19)
		mlx_destroy_image(info->win.mlx, info->tex[x].img);
	exit(0);
}

void	message(t_info *info)
{
	if (info->map.collect == 0)
	{
		printf("자네 물 좀 주겠나..?\n");
		ft_exit(info);
	}
	else
		printf("내가.. 뭐하고.. 있..었더라...?\n");
}

void	die(t_info *info)
{
	printf("나 너무 무서워.. 이러다 다 죽어!\n");
	ft_exit(info);
}

int	check_button(t_info *info)
{
	ft_exit(info);
	return (0);
}
