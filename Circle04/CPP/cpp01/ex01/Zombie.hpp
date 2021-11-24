/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:23:00 by junghan           #+#    #+#             */
/*   Updated: 2021/11/24 20:23:01 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <string>
#include <sstream>

class Zombie
{
    private:
    std::string name;

    public:
    Zombie();
    Zombie(std::string name);
    ~Zombie();
    void    announce(void);
    void    set_name(std::string name, int i);
};

Zombie* zombieHorde(int N, std::string name);
#endif
