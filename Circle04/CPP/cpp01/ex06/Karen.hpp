/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:25:44 by junghan           #+#    #+#             */
/*   Updated: 2021/11/24 20:25:45 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KAREN_HPP
# define KAREN_HPP
#include <iostream>
#include <string>

class Karen
{
	public:
    Karen();
    ~Karen();

	void complain( std::string level );

    private:
	void debug( void );
    void info( void );
    void warning( void );
    void error( void );

};
#endif
