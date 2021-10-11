/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:10:39 by junghan           #+#    #+#             */
/*   Updated: 2021/10/11 11:10:40 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		src_size;

	if (!dst || !src)
		return (0);
	src_size = ft_strlen(src);
	if (size)
	{
		while (--size && *src)
		{
			*dst = *src;
			dst++;
			src++;
		}
		*dst = '\0';
	}
	return (src_size);
}
