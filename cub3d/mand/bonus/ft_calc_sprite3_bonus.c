/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_sprite3_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:01:22 by junghan           #+#    #+#             */
/*   Updated: 2021/04/02 02:01:24 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	odd_sp(t_sprite *sprite)
{
	if (sprite->vmove2 <= -70.0)
		sprite->is_animate = 0;
	else if (sprite->vmove2 >= 70.0)
		sprite->is_animate = 1;
	if (sprite->is_animate == 1)
		sprite->vmove2 -= 0.1;
	else if (sprite->is_animate == 0)
		sprite->vmove2 += 0.1;
	return (sprite->vmove2);
}

double	even_sp(t_sprite *sprite)
{
	if (sprite->vmove <= -70.0)
		sprite->is_animate = 1;
	else if (sprite->vmove >= 70.0)
		sprite->is_animate = 0;
	if (sprite->is_animate == 1)
		sprite->vmove += 0.1;
	else if (sprite->is_animate == 0)
		sprite->vmove -= 0.1;
	return (sprite->vmove);
}
