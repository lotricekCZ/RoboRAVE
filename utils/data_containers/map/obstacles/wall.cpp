/*
 * wall.cpp
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


#include "wall.hpp"

#ifndef WALL_CPP
#define WALL_CPP

wall::wall()
	: obstacle()
{
	
}

wall::wall(coordinates edges[4])
	: obstacle()
{
	for(uint8_t i = 0; i < 4; i++){
		properties.edges[i] = edges[i];
		properties.walls[i] = line(edges[i], edges[(i != 3)? i+1: 0]);
		}	
}

bool wall::inside(coordinates a){
	coordinates AB(properties.edges[0].x - properties.edges[1].x, properties.edges[0].y - properties.edges[1].y); // coordinates used like vector
	coordinates AD(properties.edges[2].x - properties.edges[1].x, properties.edges[2].y - properties.edges[1].y); // coordinates used like vector
	coordinates AM(a.x - properties.edges[1].x, a.y - properties.edges[1].y); // coordinates used like vector
	decimal_n abam = AB.x*AM.x+AB.y*AM.y;// properties.edges[1].get_distance(properties.edges[0]);
	decimal_n abab = AB.x*AB.x+AB.y*AB.y;// properties.edges[1].get_distance(properties.edges[2]);
	decimal_n adam = AD.x*AM.x+AD.y*AM.y;// properties.edges[1].get_distance(a);
	decimal_n adad = AD.x*AD.x+AD.y*AD.y;// properties.edges[1].get_distance(a);
	//~ Ux*Vx+Uy*Vy
	
	//~ std::cout << properties.walls[0].print(properties.walls[1].make_parallel(a)) << std::endl;
	return (0 <= abam && abam <= abab) && (0 <= adam && adam <= adad);
	}

coordinates wall::is_collision_course(line l){
	coordinates inter[4] = {properties.walls[0].intersection(l, properties.walls[0]),
						properties.walls[1].intersection(l, properties.walls[1]),
						properties.walls[2].intersection(l, properties.walls[2]),
						properties.walls[3].intersection(l, properties.walls[3])};
	
	for(uint8_t i = 0; i < 4; i++)
		if (inside(inter[i]))
			return inter[i];			
	
	return coordinates(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	}
#endif
