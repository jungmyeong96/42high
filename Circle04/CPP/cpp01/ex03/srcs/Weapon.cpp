/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:24:20 by junghan           #+#    #+#             */
/*   Updated: 2021/11/24 20:35:12 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Weapon.hpp"

const std::string& Weapon::getType()
{
	return (this->type);
}

void Weapon::setType(std::string type)
{
	this->type = type;
}

Weapon::Weapon(std::string type)
{
	this->type = type;
}
