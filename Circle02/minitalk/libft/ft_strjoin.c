/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 23:12:34 by junghan           #+#    #+#             */
/*   Updated: 2021/09/11 23:12:38 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = 1;
	result = (char *)malloc(sizeof(char) * s1_len + s2_len + 1);
	if (result == 0)
		return (0);
	ft_strlcpy(result, s1, s1_len + s2_len + 1);
	ft_strlcat(result, s2, s1_len + s2_len + 1);
	free(s1);
	s1 = 0;
	return (result);
}
