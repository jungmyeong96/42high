/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:04:02 by junghan           #+#    #+#             */
/*   Updated: 2021/04/03 09:40:23 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		open_mapfile(t_info *info, char *mapfile)
{
	if (!ft_check_extation(mapfile, ".cub"))
		error_exit("Error : Invalid file.\n");
	info->fd = open(mapfile, O_RDONLY);
	if (info->fd == -1)
		error_exit("Error: Invalid file.\n");
	return (info->fd);
}

void	arg_protect(t_info *info, int argc, char **argv)
{
	int i;

	if (argc > 3)
	{
		i = 0;
		while (++i < argc)
			;
		error_exit("Error: Just put in two arguments.\n[CODE] \
				Too many arguments!\n\n");
	}
	if (argc < 2)
	{
		error_exit("Error: Just put in two arguments.\n[CODE] \
				Too few arguments!\n\n[ARGUMENTS]:\nNONE\n");
		exit(0);
	}
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7) == 0)
			info->is_save = 1;
		else
			error_exit("Error: does't save command\n[COMMAND] \
					put in --save\n\n");
	}
}
