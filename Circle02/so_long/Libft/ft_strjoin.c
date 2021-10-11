/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:10:05 by junghan           #+#    #+#             */
/*   Updated: 2021/10/11 11:10:07 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		str_len;
	char	*str;

	if (s1 == 0 || s2 == 0)
		return (0);
	str_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(str_len * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (*(s1 + i) != '\0')
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	i = 0;
	while (*(s2 + i) != '\0')
	{
		*(str + ft_strlen(s1) + i) = *(s2 + i);
		i++;
	}
	*(str + str_len - 1) = '\0';
	return (str);
}
