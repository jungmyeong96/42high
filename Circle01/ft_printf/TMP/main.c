/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:43:02 by junghan           #+#    #+#             */
/*   Updated: 2021/02/02 14:59:37 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main()
{

	char c;

	c = 'a';
	ft_printf("test1[u]:\n%u\n", -1);
	ft_printf("test2[0*.*d]:\n%*.*d\n",3,-1, 8);
	ft_printf("t3 %d\n",ft_printf("test3[.*]:\n%.*d\n",67,-2147483648));
	ft_printf("t3 %d\n",ft_printf("test4[*.4]:\n%*.4i\n",-23,42));
	ft_printf("test5ft[-16.p]:\n%-16.p\n",0);
	printf("test5[-16.p]:\n%-16.p\n",0);
}
