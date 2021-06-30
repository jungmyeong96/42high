/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 13:38:18 by junghan           #+#    #+#             */
/*   Updated: 2021/01/11 13:51:45 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	exclude_printed(char *buf, char **line, int offset)
{
	int		idx;

	if (!buf || !line)
		return ;
	if (!(*line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return ;
	idx = 0;
	while (idx < offset)
	{
		line[idx] = buf[idx];
		idx++;
	}
	ft_strcpy(buf, buf + offset);
}

int		check_null_eof(char *buf, char **line)
{
	int	idx;

	idx = 0;
	while (idx < BUFFER_SIZE)
	{
		if (buf[idx] == '\n')
		{
			return (idx);
		}
	}
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	int			readnb;
	int			offset;
	static char	*buf;
	char		*tmp;

	if (buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1))
		return (-1);
	buf[0] = '\0';
	while((readnb = read(fd, tmp, BUFFER_SIZE) > 0))
	{
		buf[readnb] = '\0';
		buf = ft_strjoin(buf, tmp);
		if((offset = check_null_eof(buf)) >= 0) /*need to fix*/ //If I don't get \n or EOF, I have to read more as buffer in loop
		{
			exclude_printed(buf, line, offset);
			return (1);
		}
	}
	return (if eof);
}
