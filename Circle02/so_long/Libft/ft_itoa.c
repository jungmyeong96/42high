/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:07:30 by junghan           #+#    #+#             */
/*   Updated: 2021/10/11 11:07:32 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_count(int n)
{
	int			count;
	long long	i;

	i = (long long)n;
	count = 0;
	if (i < 0)
	{
		count++;
		i *= -1;
	}
	while (i > 0)
	{
		i /= 10;
		count++;
	}
	return (count);
}

static void	fill_str(char *str, int n, int count)
{
	int			flag;
	long long	i;

	i = (long long)n;
	flag = 1;
	if (i < 0)
	{
		flag = -1;
		i *= -1;
	}
	count -= 1;
	while (i > 0)
	{
		str[count--] = i % 10 + '0';
		i /= 10;
	}
	if (flag == -1)
		str[count] = '-';
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;

	if (n == 0)
		return (ft_strdup("0"));
	count = itoa_count(n);
	str = (char *)ft_calloc((count + 1), sizeof(char));
	if (!str)
		return (NULL);
	fill_str(str, n, count);
	return (str);
}
