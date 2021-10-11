/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:10:26 by junghan           #+#    #+#             */
/*   Updated: 2021/10/11 11:10:28 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	int		i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if ((unsigned long)(dst_len + 1) < size)
	{
		while (src[i] && i < (int)(size - dst_len - 1))
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
	}
	if (size < dst_len)
		return (src_len + size);
	else
		return (src_len + dst_len);
}
