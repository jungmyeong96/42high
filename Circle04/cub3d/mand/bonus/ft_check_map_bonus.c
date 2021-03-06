/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:02:43 by junghan           #+#    #+#             */
/*   Updated: 2021/04/03 09:41:04 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_char(int c)
{
	if (!(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5'
				|| c == '6' || c == '7' || c == '8' || c == 'N' || c == 'E'
				|| c == 'W' || c == 'S'))
	{
		error_exit("Error: map invalid\
				\n[CODE] another char in the map\n");
	}
}

void	check_back_len(char **map, int y, int j)
{
	int len;

	len = ft_strlen(map[y]);
	if (len < j && map[y + 1][j] != 1)
		error_exit("Error: map invalid\
				\n[CODE] back strlen is too short\n");
}

void	check_front_len(char **map, int y, int j)
{
	int len;

	len = ft_strlen(map[y]);
	if (len < j && map[y - 1][j] != 1)
		error_exit("Error: map invalid\
				\n[CODE] front strlen is too short\n");
}

void	check_one_y(char **map, int i, int j, t_info *info)
{
	int		y;

	y = i;
	while (--y >= -1)
	{
		if (y == -1)
			error_exit("Error: map invalid\
					\n[CODE] y up index\n");
		check_back_len(map, y, j);
		if (map[y][j] == '1')
			break ;
		check_char(map[y][j]);
	}
	y = i;
	while (++y <= info->map_lines)
	{
		if (y == info->map_lines)
			error_exit("Error: map invalid\
					\n[CODE] y down index \n");
		check_front_len(map, y, j);
		if (map[y][j] == '1')
			break ;
		check_char(map[y][j]);
	}
}

void	check_one_x(char **map, int i, int j, t_info *info)
{
	int x;

	if (map[i][j] == '2' || map[i][j] == '3' || map[i][j] == '4' ||
			map[i][j] == '5' || map[i][j] == '6' || map[i][j] == '7'
			|| map[i][j] == '8')
		count_item(map[i][j], info);
	x = j;
	while (--x >= 0)
	{
		if (map[i][x] == '1')
			break ;
		check_char(map[i][x]);
		if (x == 0)
			error_exit("Error: map invalid\n[CODE] x_left_idx\n");
	}
	x = j;
	while (map[i][x] != '\0')
	{
		if (map[i][x] == '1')
			break ;
		check_char(map[i][x]);
		if (map[i][++x] == '\0')
			error_exit("Error: map invalid\n[CODE] x_right_idx\n");
	}
	check_one_y(map, i, j, info);
}
