/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:44:55 by junghan           #+#    #+#             */
/*   Updated: 2021/07/20 12:12:40 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key_press2(int key_num, t_keys *keys)
{
	if (key_num == K_AR_R)
		keys->key_right = 1;
	if (key_num == K_AR_L)
		keys->key_left = 1;
	if (key_num == K_ESC)
		exit(0);
	return (0);
}

int	ft_key_press(int key_num, t_keys *keys)
{
	if (key_num == K_W)
		keys->key_w = 1;
	if (key_num == K_S)
		keys->key_s = 1;
	if (key_num == K_D)
		keys->key_d = 1;
	if (key_num == K_A)
		keys->key_a = 1;
	ft_key_press2(key_num, keys);
	return (0);
}

int	ft_key_release2(int key_num, t_keys *keys)
{
	if (key_num == K_AR_R)
	{
		keys->key_right = 0;
		keys->key_eq = 0;
	}
	if (key_num == K_AR_L)
	{
		keys->key_left = 0;
		keys->key_qe = 0;
	}
	if (key_num == K_ESC)
		exit(0);
	return (0);
}

int	ft_key_release(int key_num, t_keys *keys)
{
	if (key_num == K_W)
	{
		keys->key_w = 0;
		keys->key_ws = 0;
	}
	if (key_num == K_S)
	{
		keys->key_s = 0;
		keys->key_sw = 0;
	}
	if (key_num == K_D)
	{
		keys->key_d = 0;
		keys->key_da = 0;
	}
	if (key_num == K_A)
	{
		keys->key_a = 0;
		keys->key_ad = 0;
	}
	ft_key_release2(key_num, keys);
	return (0);
}

int	ft_click_exit(int keys, t_info *info)
{
	info->click = keys;
	exit(0);
	return (0);
}
