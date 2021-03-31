/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sound.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 23:48:22 by junghan           #+#    #+#             */
/*   Updated: 2021/03/30 22:25:45 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	stage_sound(t_info *info)
{
//	printf("ss %d\n", info->stage_sound);
	if (info->stage_end == 0)
	{
		system("pkill afplay");
		system("afplay ../sound/terranbgm.wav &");
	}
	else if (info->stage_end == 1)
	{
		system("pkill afplay");
		system("afplay ../sound/zergbgm.wav &");
	}
	else if (info->stage_end == 2)
	{
		system("pkill afplay");
		system("afplay ../sound/protossbgm.wav &");
	}
//	if (info->stage_sound == 1)
//		system("afplay ../sound/tankwall.wav &");
}

void	hit_sound(t_info *info, int tex, t_s *mob)
{
	if (mob->hit == 0)
	{
		if (tex == 10 && info->stage_end == 0)
			system("afplay ../sound/maqoute.wav &");
		if (tex == 10 && info->stage_end == 1)
			system("afplay ../sound/hydqoute.wav &");
		if (tex == 10 && info->stage_end == 2)
			system("afplay ../sound/draqoute.wav &");
		if (tex == 14 && info->stage_end == 0)
			system("afplay ../sound/scvqoute.wav &");
		if (tex == 14 && info->stage_end == 1)
			system("afplay ../sound/eggqoute.wav &");
		if (tex == 14 && info->stage_end == 2)
			system("afplay ../sound/interqoute.wav &");
		if (tex == 15 && info->stage_end == 0)
			system("afplay ../sound/ghostqoute.wav &");
		if (tex == 15 && info->stage_end == 1)
			system("afplay ../sound/mutalqoute.wav &");
		if (tex == 15 && info->stage_end == 2)
			system("afplay ../sound/carriqoute.wav &");
	}
}

void	death_sound(t_info *info, int tex)
{
	if (tex == 10 && info->stage_end == 0)
		system("afplay ../sound/madth.wav &");
	if (tex == 10 && info->stage_end == 1)
		system("afplay ../sound/hydth.wav &");
	if (tex == 10 && info->stage_end == 2)
		system("afplay ../sound/dradth.wav &");
	if (tex == 14 && info->stage_end == 0)
		system("afplay ../sound/scvdth.wav &");
	if (tex == 14 && info->stage_end == 1)
		system("afplay ../sound/eggdth.wav &");
	if (tex == 14 && info->stage_end == 2)
		system("afplay ../sound/interdth.wav &");
	if (tex == 15 && info->stage_end == 0)
		system("afplay ../sound/ghostdth.wav &");
	if (tex == 15 && info->stage_end == 1)
		system("afplay ../sound/mutaldth.wav &");
	if (tex == 15 && info->stage_end == 2)
		system("afplay ../sound/carridth.wav &");

}
