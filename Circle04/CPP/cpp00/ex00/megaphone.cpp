/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:08:52 by junghan           #+#    #+#             */
/*   Updated: 2021/11/23 20:08:59 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int	main(int argc, char **argv)
{
	int	idx;

	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	idx = 0;
	while (++idx < argc)
	{
		for (int i = 0; argv[idx][i] != 0; i++)
		{
			std::cout << static_cast<char>(toupper(argv[idx][i]));
		}
	}
	std::cout << std::endl;
	return (0);
}
