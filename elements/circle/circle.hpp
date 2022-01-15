/*
 * circle.hpp
 * 
 * Copyright 2021 Jakub Ramašeuski <jakub@skaryna.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <cmath> 
#include <string> 
#include <vector> 
#include <array> 
//~ #include "include.hpp"
#include <limits>
#include <string>
#include <iostream>
#include <inttypes.h>

#include "../../defines/constants.h"
#include "../../utils/data_containers/coordinates/coordinates.hpp"

#include "../line/line.hpp"

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

class circle{
	public:
		decimal_n radius = 1;
		coordinates center;
		circle(coordinates c, decimal_n r = 0);
		circle(decimal_n x = 0, decimal_n y = 0, decimal_n r = 0);
		static std::vector<circle> circles(line, line, decimal_n radius = 1);
		
		bool inside(coordinates a);
		bool inside(decimal_n x, decimal_n y);
		bool is_on(coordinates c, decimal_n thresh = 1e-3);
		
		static void circle_tangents(coordinates c, decimal_n r1, decimal_n r2, std::vector<line> & ans);
		static std::vector<coordinates> tangent_points(circle c, coordinates point);
		std::vector<coordinates> points();
		
		static std::vector<coordinates> intersection(line, circle); // function to decide if sth intersects
		static std::vector<coordinates> intersection(circle k, circle c);
		
		std::vector<coordinates> intersection(line);		 // function to decide if sth intersects
		std::vector<coordinates> intersection(circle);
		
		std::vector<coordinates> tangent_points(coordinates point);
		static std::vector<line> tangents(circle c, coordinates point);
		std::vector<line> tangents(coordinates point);
		static std::vector<line> circle_tangents(circle a, circle b);
		std::string print();
		
		static decimal_n get_distance(circle, coordinates);
		static decimal_n get_distance(circle, line);
		static decimal_n get_distance(circle, coordinates, coordinates);
		
		decimal_n get_distance(coordinates);
		decimal_n get_distance(line);
		decimal_n get_distance(coordinates, coordinates);
		
		bool on_segment(coordinates, coordinates, coordinates, bool);
		inline bool operator==(const circle& rhs){ 
			return this -> center == rhs.center && this -> radius == rhs.radius;
			}
			
		inline bool operator!=(const circle& rhs){ 
			return !(*this == rhs)	;
			}
			
		inline circle operator+(const decimal_n& rhs){ 
			return circle(this -> center, this -> radius + rhs);
			}
			
		inline circle operator-(const decimal_n& rhs){ 
			return circle(this -> center, (this -> radius - rhs < 0)? 0 : this -> radius - rhs);
			}
	private:
		/* add your private declarations */
};

#endif /* OBSTACLE_HPP */ 
