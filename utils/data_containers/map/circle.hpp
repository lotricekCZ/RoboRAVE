/*
 * obstacle.hpp
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


#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "obstacle.cpp"

class circle: public obstacle {
	public:
		decimal_n radius_c = 1;
		coordinates center;
		circle();
		bool inside(coordinates a);
		bool inside(decimal_n x, decimal_n y);
		std::vector<coordinates> points();
		bool is_collision_course();
	private:
		/* add your private declarations */
};

#endif /* OBSTACLE_HPP */ 
