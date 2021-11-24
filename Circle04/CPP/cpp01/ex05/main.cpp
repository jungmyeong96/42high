/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:26:11 by junghan           #+#    #+#             */
/*   Updated: 2021/11/24 20:38:02 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

int     main(void)
{
    Karen   karen;

    karen.complain("ERROR");
    karen.complain("DEBUG");
    karen.complain("WARNING");
    karen.complain("INFO");
}
