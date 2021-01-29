/*
 * wall.hpp
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


#ifndef WALL_HPP
#define WALL_HPP

#include "obstacle.cpp"

class wall: public obstacle
{
	static uint8_t 	count;
	public:
	
	struct{
		line 		walls[4];
		coordinates edges[4];
		uint8_t 	id;
		} properties;
	location::type _type = location::_barrier;
	
		wall();
		wall(coordinates[4]);
		bool inside(coordinates a);
		bool inside(decimal_n x, decimal_n y){return false;}
		std::vector<coordinates> points(){return std::vector<coordinates> ();}
		std::vector<coordinates>  is_collision_course(line);
		std::vector<coordinates>  is_collision_course(circle);
	private:
		/* add your private declarations */
};

#endif /* WALL_HPP */ 
