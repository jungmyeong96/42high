/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:53:31 by junghan           #+#    #+#             */
/*   Updated: 2021/02/02 20:10:33 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int main()
{
	char c;
	
	c = 1;
	ft_printf("2-%.c",c);
	ft_printf("%d", 8);
	ft_printf("%s", "asdfad");
	ft_printf("%p", &c);
	ft_printf("%u", 1213);
	ft_printf("%x", 123213);
	while(1)
		;
}
