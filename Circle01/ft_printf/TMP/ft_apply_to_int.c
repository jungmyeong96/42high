/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_to_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:13:23 by junghan           #+#    #+#             */
/*   Updated: 2021/02/02 14:01:04 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		ft_apply_to_int(va_list *ap, t_info info, int *result)
{
	char			*int_str;
	long long int	num;
	int				sign;

	sign = 1;
	num = va_arg(*ap, int);
	if (num < 0)
	{
		sign = -1;
		(*result)++;
	}
	if (!(int_str = ft_itoa(num * sign)))
		return (0);
	if (info.p_num < 0 && info.p_asterisk == NO)
		return (0);
	if (num == 0 && ((info.p_existence == DOTNUM && info.p_num == 0)
				|| info.p_existence == ONLYDOT))
	{
		(*result) += info.w_num;
		while (info.w_num--)
			write(1, " ", sizeof(char));
		return (1);
	}
	(*result) += ft_print_int(int_str, info, sign);
	return (1);
}

int		ft_apply_to_unint(va_list *ap, t_info info, int *result)
{
	char			*int_str;
	unsigned int	un_num;
	int				sign;
	char			*tmp;

	sign = 1;
	un_num = va_arg(*ap, unsigned int);
	*tmp = un_num % 10 + '0';
	if (!(int_str = ft_itoa(un_num / 10)))
		return (0);
	int_str = ft_strjoin(int_str, tmp);
	if (info.p_num < 0 && info.p_asterisk == NO)
		return (0);
	if (un_num == 0 && ((info.p_existence == DOTNUM && info.p_num == 0)
			|| info.p_existence == ONLYDOT))
	{
		(*result) += info.w_num;
		while (info.w_num--)
			write(1, " ", sizeof(char));
		return (1);
	}
	(*result) += ft_print_int(int_str, info, sign);
	free(int_str);
	int_str = 0;
	return (1);
}

int		ft_apply_to_hex(va_list *ap, const char *spec, t_info info, int *result)
{
	char			*hex_str;
	unsigned int	to_hex;
	int				sign;

	sign = 1;
	to_hex = va_arg(*ap, unsigned int);
	if (!(hex_str = ft_chg_to_hex(to_hex, spec)))
		return (0);
	if (info.p_num < 0 && info.p_asterisk == NO)
		return (0);
	if (to_hex == 0 && ((info.p_existence == DOTNUM && info.p_num == 0)
				|| info.p_existence == ONLYDOT))
	{
		(*result) += info.w_num;
		while (info.w_num--)
			write(1, " ", sizeof(char));
		return (1);
	}
	(*result) += ft_print_int(hex_str, info, sign);
	free(hex_str);
	hex_str = 0;
	return (1);
}
