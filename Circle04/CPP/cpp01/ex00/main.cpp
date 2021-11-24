/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:22:30 by junghan           #+#    #+#             */
/*   Updated: 2021/11/24 20:22:31 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int     main(void)
{
    Zombie* newzombie;
    
    newzombie = newZombie("monika");
    newzombie->announce();
    randomChump("leejung");
    delete newzombie;
    return (0);
}
