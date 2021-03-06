/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:41:22 by junghan           #+#    #+#             */
/*   Updated: 2021/03/02 23:48:38 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_frontcount(char *s1, char *set)
{
	int	i;
	int s1_len;

	s1_len = ft_strlen(s1);
	i = 0;
	while (s1[i])
	{
		if (ft_strchr(set, s1[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

static int	ft_backcount(char *s1, char *set)
{
	int	i;
	int s1_len;

	i = 0;
	s1_len = ft_strlen(s1);
	while (s1[i])
	{
		if (ft_strchr(set, s1[s1_len - i - 1]) == 0)
			return (s1_len - i);
		i++;
	}
	return (s1_len - i);
}

char		*ft_strtrim(char *s1, char *set)
{
	char	*result;
	int		front;
	int		back;

	if (!s1 || !set)
		return (0);
	front = ft_frontcount(s1, set);
	back = ft_backcount(s1, set);
	if (front >= back)
		return (ft_strdup(""));
	if (!(result = (char *)malloc(sizeof(char) * (back - front + 1))))
		return (0);
	ft_strlcpy(result, s1 + front, back - front + 1);
	return (result);
}
