/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 23:13:45 by junghan           #+#    #+#             */
/*   Updated: 2021/09/11 23:13:48 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	char	*tmp;
	int		len;

	len = ft_strlen(s1);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (tmp == 0)
		return (0);
	ft_strlcpy(tmp, s1, len + 1);
	return (tmp);
}
