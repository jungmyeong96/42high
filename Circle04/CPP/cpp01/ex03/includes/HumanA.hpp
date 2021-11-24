/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:24:06 by junghan           #+#    #+#             */
/*   Updated: 2021/11/24 20:24:07 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP
# include "../includes/Weapon.hpp"

class HumanA
{
	private:
		std::string name;
		Weapon &weapon;
		
	public:
		HumanA(std::string name, Weapon &weapon);
		void attack();
};

#endif
