/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:43:02 by junghan           #+#    #+#             */
/*   Updated: 2021/01/29 21:46:46 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main()
{

		ft_printf("test1[-0--0100.7d]:\n%-0--0100.7d\n", 10);
		ft_printf("test2[-010.3d]:\n%-010.3d\n", 1);
		ft_printf("test3[.*]:\n%.*d\n",67,5);
		ft_printf("test4[*.4i]:\n%*.4i\n",-23,42);
  		ft_printf("test5[-0*.*d]:\n%-0*.*d\n",-123,-23,20);
		ft_printf("test6[*s:\n%*s\n", 23,"afdasdfasdf sd  f");
		ft_printf("test7[000*s]:\n%000*s\n",1,"asfsdfsdfdsf sd fsdsadf");
		ft_printf("test8[d]:\n%d\n",1,10);
}

