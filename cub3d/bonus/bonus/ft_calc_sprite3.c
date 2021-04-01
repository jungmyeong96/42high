/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_sprite3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 23:52:51 by junghan           #+#    #+#             */
/*   Updated: 2021/04/01 23:53:17 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
