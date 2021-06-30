/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:49:20 by junghan           #+#    #+#             */
/*   Updated: 2021/01/13 15:53:30 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int	find_new(const char *save, char c)
{
	int		idx;

	idx = 0;
	while(save[idx])
	{
		if (save[idx] == '\n')
			return (idx);
		idx++;
	}
	return(-1);
}

int	cut_string(char **save, char **line, int cut_point)
{
	char	*tmp;

	(*save)[cut_point] = '\0';
	*line = ft_strdup(*save);
	tmp = ft_strdup((*save) + cut_point + 1);
	free(*save);
	*save = tmp;
	return (1);
}

int	put_all(char **save, char **line, int offset)
{
	int		cut_point;

	if (offset < 0)
		return (-1);
	if (*save && ((cut_point = find_new(*save, '\n')) >= 0))
		return (cut_string(save, line, cut_point));
	if (*save)
	{
		*line = *save;
		*save = 0;
	}
	else
		*line = ft_strdup(""); //if file has only NULL or has only last idx
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int			offset;
	int			cut_point;
	static char	*save;
	char		*tmp;
	char		buf[BUFFER_SIZE + 1];

	if (!fd || !line || BUFFER_SIZE <= 0)//check parameter & check BUFFER
		return (-1);
	while ((offset = read(fd, buf, BUFFER_SIZE)) > 0) //check read_file //+check ft_strcut (option)
	{
		buf[offset] = '\0';
		if (save)
			tmp = ft_strjoin(save, buf);
		else
			tmp = ft_strdup(buf);
		if (save)
			free(save);
		save = tmp;
		if ((cut_point = find_new(save, '\n')) >= 0)
			return(cut_string(&save, line, cut_point));
	}
	return(put_all(&save, line, offset));
}
