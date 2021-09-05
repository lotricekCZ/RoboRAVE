/*
 * candle.hpp
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


#include "obstacle.hpp"
#include "../include.hpp"

#ifndef CANDLE_HPP
#define CANDLE_HPP


class candle: public obstacle
{
	public:
		location::type _type = location::_candle;
		circle tube;
		
		candle();
		candle(coordinates);
		
		bool inside(coordinates a){return tube.inside(a);}
		bool inside(decimal_n x, decimal_n y){return tube.inside(x, y);}
		std::vector<coordinates> points(){return std::vector<coordinates> ();}
		std::vector<coordinates> is_collision_course(line l){return tube.intersection(l, tube);}
		std::vector<coordinates> is_collision_course(circle c){return tube.intersection(c, tube);}
		std::array<coordinates, 2> get_box(){return {tube.center - coordinates(tube.radius, tube.radius), tube.center + coordinates(tube.radius, tube.radius)};};
		std::string inkscape_print();
	private:
		/* add your private declarations */
};

#endif /* CANDLE_HPP */ 
