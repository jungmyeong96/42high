/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_attack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 05:45:47 by junghan           #+#    #+#             */
/*   Updated: 2021/03/31 00:34:36 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_sp_demege2(t_sprite *sprite, t_info *info, int x, int tex)
{
	int		y;

	y = sprite->drawstart_y - 1;
	while (++y < sprite->drawend_y)
	{
		sprite->di = (y - sprite->vmove_scr)
			* 256 - info->win_hei * 128 +
			sprite->sprite_hei * 128;
		sprite->tex_y = ((sprite->di * info->texwh[tex].tex_h)
				/ sprite->sprite_hei) / 256;
		sprite->color = info->texture[tex][info->texwh[tex].tex_w *
			sprite->tex_y + sprite->tex_x];
		info->sp_h = sprite->drawend_y - sprite->drawstart_y;
		sprite_shadow(info, sprite);
		if ((sprite->color & 0x00FFFFFF) != 0)
			info->buf[y][x] = sprite->color * 2 & 7755711;
	}
	info->sp_hit = 0;
}

void	put_sp_demege1(t_sprite *sprite, t_info *info, t_s *mob, int tex)
{
	int		x;
	
	mob->hit++;
	x = sprite->drawstart_x - 1;
	while (++x < sprite->drawend_x && tex != 0)
	{
		sprite->tex_x = (int)(256 * (x - (-sprite->sprite_wid
						/ 2 + sprite->sprite_scr_x))
				* info->texwh[tex].tex_w / sprite->sprite_wid) / 256;
		if (sprite->transf_y > 0 && x > 0 && x < info->win_wid
				&& sprite->transf_y < info->z_buffer[x])
				put_sp_demege2(sprite, info, x, tex);
	}
}

void	is_boss_or_mob(int tex, int *hp)
{
	if (tex == 10)
		*hp = 55;
	else if (tex == 14)
		*hp = 30;
	else if (tex == 15)
		*hp = 150;
}

void	sp_or_dam(t_info *info, t_sprite *s, t_s *mob, int tex)
{
	int hp;

	is_boss_or_mob(tex, &hp);
	put_in_spritebuf(s, info, tex);
	if ((info->sp_hit == 1 && s->save_mob == s->one_mob)
			|| (info->skill_t != 0 && s->save_mob == s->one_mob))
	{
		if (info->sp7 != 0 && info->stage_end == 2 && tex == 15)
			return ;
		hit_sound(info, tex, mob);
		put_sp_demege1(s, info, mob, tex);
	}
	if (mob->hit >= hp)
	{
		death_sound(info, tex);
		info->map[(int)mob->x][(int)mob->y] = '0';
		mob->x = 0;
		mob->y = 0;
		mob->tex = 0;
		mob->hit = 0;
		if (tex == 14 && info->stage_end == 1)
			info->slow = 0;
		if (info->stage_end == 2 && tex == 14)
			info->sp7--;
	}
}

void	attack(t_info *info, t_img *img, char *path)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(info->mlx,
			path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian);
	tex_wh(info, 18, img);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			info->texture[18][img->img_width * y + x] =
				img->data[img->img_width * y + x];
	}
	mlx_destroy_image(info->mlx, img->img);
	if (info->skill1 && info->skill_t < 1)
		system("afplay ../sound/rifle.wav &");
	info->skill_t++;
	if (info->skill_t == 20)
	{
		info->sprite.save_mob = -1;
		info->skill1 = 0;
		info->skill_t = 0;
	}
	put_in_weapon(info, img, 18);
}

int			click_r(int b, int x, int y, t_info *info)
{
	x = 0;
	y = 0;
	if (b == 0)
		info->skill1 = 0;
	return (0);
}

int			click(int b, int x, int y, t_info *info)
{
	x = 0;
	y = 0;
	if (b == 1 && info->keys.key_p == 1 && info->weapon == 1)
		info->skill1 = 1;
	return (0);
}
