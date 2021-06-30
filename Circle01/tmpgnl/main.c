/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 20:02:15 by junghan           #+#    #+#             */
/*   Updated: 2021/01/14 00:10:58 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <string.h>

int	main(int ac, char **av)
{
	char	*line;
	int		check;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	while (ac >= 1 && fd < 0)
	{
		if (ac >= 2)
			fd = open(*(++av), O_RDONLY);
		else
			fd = 0;
		while ((check = get_next_line(fd, &line)) > 0)
		{
			printf("%s\n", line);
			free(line);
		}
		ac--;
	}
	printf("%s\n", line);
	free(line);
	close(fd);
	return (0);
}
