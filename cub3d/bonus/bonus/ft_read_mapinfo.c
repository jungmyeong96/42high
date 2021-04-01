/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_mapinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:36:34 by junghan           #+#    #+#             */
/*   Updated: 2021/04/02 00:08:09 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_dup(t_info *info)
{
	int		i;

	i = -1;
	while (++i < 7)
	{
		if (info->check_ele[i] > 1)
			error_exit("Error : element duplicate!\n");
		else if (info->check_ele[i] == 0)
			error_exit("Error : wrong element!\n");
	}
}

void	check_arg(t_info *info, char *d)
{
	if (ft_strncmp(d, "R", 2) == 0)
		info->check_ele[0] += 1;
	else if (ft_strncmp(d, "NO", 3) == 0)
		info->check_ele[1] += 1;
	else if (ft_strncmp(d, "SO", 3) == 0)
		info->check_ele[2] += 1;
	else if (ft_strncmp(d, "WE", 3) == 0)
		info->check_ele[3] += 1;
	else if (ft_strncmp(d, "EA", 3) == 0)
		info->check_ele[4] += 1;
	else if (ft_strncmp(d, "F", 2) == 0)
		info->check_ele[5] += 1;
	else if (ft_strncmp(d, "C", 2) == 0)
		info->check_ele[6] += 1;
}

int		check_element2(t_info *info, char **data)
{
	if (!ft_strncmp(data[0], "NXT", 4))
		info->stage = ft_strdup(data[1]);
	else if (!ft_strncmp(data[0], "NO", 3))
		tex_data(info, data[1], 0);
	else if (!ft_strncmp(data[0], "SO", 3))
		tex_data(info, data[1], 1);
	else if (!ft_strncmp(data[0], "WE", 3))
		tex_data(info, data[1], 2);
	else if (!ft_strncmp(data[0], "EA", 3))
		tex_data(info, data[1], 3);
	else if (!ft_strncmp(data[0], "S", 2))
		sp_data(info, data);
	else if (!ft_strncmp(data[0], "F", 2))
		col_or_xpm(info, data[1], 5);
	else if (!ft_strncmp(data[0], "C", 2))
		col_or_xpm(info, data[1], 6);
	else if (is_space(data[0], info) == 0)
		return (-1);
	else
		return (-1);
	return (0);
}

int		check_element(t_info *info, char **data)
{
	int result;

	result = 0;
	check_arg(info, data[0]);
	if (!ft_strncmp(data[0], "R", 2))
		screen_size(info, data[1], data[2]);
	else
		result = check_element2(info, data);
	if (result == -1)
		return (-1);
	if (info->check_ele[6] == 1)
		return (-1);
	return (0);
}

void	get_file(t_info *info)
{
	char	*line;
	char	**data;

	while (get_next_line(info->fd, &line) > 0)
	{
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		data = ft_split(line, ' ');
		if (data == 0)
			error_exit("[ERROR] split fail");
		if ((info->ele = check_element(info, data)) == -1)
			check_dup(info);
		free_dou(data);
		free(line);
		if (info->ele == -1)
			break ;
	}
}
