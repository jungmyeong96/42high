/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 00:22:54 by junghan           #+#    #+#             */
/*   Updated: 2021/01/10 13:38:08 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
char *read_file(int fd)
{
	char *tmp;

	if(!(*tmp = (char *)malloc(sizeof(char) * BUFFER_SIZE)))
		return (0);
	if(read(fd, tmp, BUFFER_SIZE) < 0)
		return (0);
	return (tmp);
}

int find_null_eof(char *tmp)
{
	int start;
	int end;
	int idx;

	start = 0;
	end = 0;
	idx = 0;
	while (idx < BUFFER_SIZE)
	{
		if (tmp[idx] == '\n' || tmp[idx] == EOF)
			return (idx);
		idx++;
	}
	return (idx);
}

void set_line(int max, char **line, char *tmp)
{
	int	idx;

	idx = 0;
	while(idx < max)
	{
		*line[idx] = tmp[idx];
		idx++;
	}
}

int	get_next_line(int fd, char **line)
{
	int idx;
	static char *tmp;

	if (!(*line = (char *)malloc(sizeof(char) * BUFFER_SIZE)))
		return (-1);
	tmp = read_file(fd);
	idx = find_null_eof(tmp);
	set_line(idx, line, tmp);

	return (1);
}
