/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:23:05 by junghan           #+#    #+#             */
/*   Updated: 2021/11/24 20:23:07 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int     main(void)
{
    Zombie* zombies;
    int     N;

    N = 8;
    zombies = zombieHorde(N, "noze");
    for (int i = 0; i < N; i++)
    {
        zombies[i].announce();
    }
    delete[] zombies;
    return (0);
}
