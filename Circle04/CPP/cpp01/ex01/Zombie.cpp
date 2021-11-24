/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:22:57 by junghan           #+#    #+#             */
/*   Updated: 2021/11/24 20:22:59 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie()
{
    name = "daekim";
}

Zombie::Zombie(std::string name)
{
    this->name = name;
}

void    Zombie::announce(void)
{
    std::cout << name << " BraiiiiiiinnnzzzZ..." << std::endl;
}

void    Zombie::set_name(std::string name, int i)
{
    std::string str;
    std::stringstream num;
    
    num << i;
    str = num.str();
    this->name = name + str;
}

Zombie::~Zombie()
{
    std::cout << name << " is down..." << std::endl;
}
