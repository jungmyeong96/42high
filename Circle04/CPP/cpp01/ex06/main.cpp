/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:25:48 by junghan           #+#    #+#             */
/*   Updated: 2021/11/24 20:39:40 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

int     main(int argc, char **argv)
{
    Karen   karen;

    if (argc != 2)
    {
        std::cout << "What do you want for me..?" << std::endl;
        return (-1);
    }
    karen.complain(static_cast<std::string>(argv[1]));
    return (0);
}
