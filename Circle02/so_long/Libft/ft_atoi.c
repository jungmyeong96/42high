/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:05:33 by junghan           #+#    #+#             */
/*   Updated: 2021/10/11 11:05:46 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long int	flag;
	long long int	result;

	while ((9 <= *str && *str <= 13) || (*str == ' '))
		str++;
	flag = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		flag *= -1;
		str++;
	}
	result = 0;
	while ('0' <= *str && *str <= '9')
	{
		result = result * 10 + *str - '0';
		if (flag < 0 && result > 2147483648)
			return (0);
		else if (flag > 0 && result > 2147483647)
			return (-1);
		str++;
	}
	return ((int)(flag * result));
}
