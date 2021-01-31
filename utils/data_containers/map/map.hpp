/*
 * map.hpp
 * 
 * Copyright 2020 Jakub Ramašeuski <jakub@skaryna.net>
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


#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <variant>
#include "location.cpp"
#include "../../../defines/constants.h"

class map
{
	public:
		std::vector<location> _map;
		
		std::vector<wall> _map_walls;
		std::vector<candle> _map_candles;
		std::vector<surround_circle> _map_surround_circles;
		
		std::vector<location *> strip(std::array<coordinates, 2>);
		location interest_calculate();
		location interest_maximal(std::vector<location> inmap);
		void interest_map();
		map();
		void append(location);
		
		/// appends obstacles to their maps
		void append(wall);
		void append(candle);
		void append(surround_circle);
		
		/// alters map on specific coordinates
		void edit_map(wall);
		//~ void edit_map(candle);
		//~ void edit_map(surround_circle);
		
		
		
		decimal_n calculate_location(location lo);
		//~ void alter(location);
		std::vector<location> grid(signed_b, signed_b, signed_b, signed_b);
	private:
		/* add your private declarations */
};

			
#endif /* MAP_HPP */ 
