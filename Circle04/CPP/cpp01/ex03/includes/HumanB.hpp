/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:24:08 by junghan           #+#    #+#             */
/*   Updated: 2021/11/24 20:24:09 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP
# include "../includes/Weapon.hpp"

class HumanB
{
	private:
		std::string name;
		Weapon *weapon;
	public:
		HumanB(std::string name);
		void attack();
		void setWeapon(Weapon *weapon);
};

#endif
