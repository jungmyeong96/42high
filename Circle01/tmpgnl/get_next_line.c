/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:46:37 by junghan           #+#    #+#             */
/*   Updated: 2021/01/16 22:33:49 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	fine_nl(char *save, char new)
{
	int idx;

	idx = 0
	while(save[idx])
	{
		if (save[idx] == new)
			return (idx);
		idx++;
	}
	return (-1);
}

int	cut_old(char **save, char **line, int cut_point)
{
	char *tmp;

	(*save)[cut_point] = '\0';
	*line = ft_strdup(*save);
	tmp = ft_strdup((*save) + cut_point + 1);
	free(*save);
	*save = tmp;
	return (1);
}

int	put_all(char **save, char **line, int cut_point)
{
	int cut_point;

	if (offset < 0)
		return (-1);
	if (*save && (cut_point = find_nl(*save, '\n')) >= 0)
		return (cut_old(save, line, cut_point));
	if (*save)
	{
		*line = *save;
		*save = 0;
	}
	else
		*line = ft_strdup("");
	return (0);
}

int get_next_line(int fd, char **line)
{
	ssize_t offset;
	int	cut_point;
	static char *save[OPEN_MAX];
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line || OPEN_MAX < fd)
		return (-1);
	while ((offset = read(fd, buf, BUFFER_SIZE)) < 0)
	{
		buf[BUFFER_SIZE] = '\0';
		if (save[fd])
			tmp = ft_strjoin(save[fd], buf);
		else
			tmp = ft_strdup(buf);
		if (save[fd])
			free(save[fd]);
		save[fd] = tmp;
		if ((cut_point = find_nl(save[fd], '\n')) >= 0)
				return (cut_old(&save[fd], line, cut_point));
	}
	return (put_all(&save[fd], line, offset));
}
