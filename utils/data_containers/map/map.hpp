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
#include "location.cpp"
#include "../../../defines/constants.h"

class map
{
	public:
		std::vector<location> _map;
		location interest_calculate();
		location interest_maximal(std::vector<location> inmap);
		void interest_map();
		map();
		void append(location);
		decimal_n calculate_location(location lo);
		//~ void alter(location);
		std::vector<location> grid(int, int, int, int);
	private:
		/* add your private declarations */
};

			
#endif /* MAP_HPP */ 
