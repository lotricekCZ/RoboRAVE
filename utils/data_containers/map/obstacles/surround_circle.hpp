/*
 * surround_circle.hpp
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


#include "../include.hpp"
#include "obstacle.hpp"

#ifndef SURROUND_CIRCLE_HPP
#define SURROUND_CIRCLE_HPP

class surround_circle: public obstacle
{
	public:
		location::type _type = location::_line_surround;
		circle inner;
		circle outer;
		
		surround_circle(coordinates);
		bool inside(coordinates a){return outer.inside(a);}
		bool inside(decimal_n x, decimal_n y){return outer.inside(x, y);}
		std::vector<coordinates> points(){return std::vector<coordinates> ();}
		std::vector<coordinates> is_collision_course(line l){return outer.intersection(l);}
		std::vector<coordinates> is_collision_course(circle c){return outer.intersection(c);}
		std::array<coordinates, 2> get_box(){return {outer.center - coordinates(outer.radius, outer.radius), outer.center + coordinates(outer.radius, outer.radius)};};
		std::string inkscape_print();
	private:
		/* add your private declarations */
};

#endif /* CANDLE_HPP */ 
