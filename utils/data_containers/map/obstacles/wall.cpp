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
		properties.walls[i] = line(edges[i], edges[(i+1)%4]);
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

std::vector<coordinates> wall::is_collision_course(line l){
	std::vector<coordinates> inter;
	for(uint8_t i = 0; i < 4; i++){
		coordinates a = (properties.walls[i].intersection(l, properties.walls[i]));
		if (inside(a))
			inter.push_back(a);
	}
	
	return inter;
	}


std::vector<coordinates>  wall::is_collision_course(circle c){
	std::vector<coordinates> inter;
	for(uint8_t i = 0; i < 4; i++){
		std::vector<coordinates> b = c.intersection(properties.walls[i], c);
		for(auto a: b)
			if (inside(a))
				inter.push_back(a);
	}
	
	return inter;
	
	}

std::array<coordinates, 2> wall::get_box(){
	decimal_n min_x = properties.edges[0].x, min_y = properties.edges[0].y, 
				max_x = properties.edges[0].x, max_y = properties.edges[0].y;
	for(uint8_t i = 1; i < 4; i++){
		min_x = (min_x > properties.edges[i].x)? min_x : properties.edges[i].x;
		min_y = (min_y > properties.edges[i].y)? min_y : properties.edges[i].y;
		
		max_x = (max_x < properties.edges[i].x)? max_x : properties.edges[i].x;
		max_y = (max_y < properties.edges[i].y)? max_y : properties.edges[i].y;
		}
	return {coordinates(min_x, min_y), coordinates(max_x, max_y)};
	}

std::string wall::inkscape_print(){
	return "<rect \n\
	inkscape:transform-center-y=\"-20\"\
    inkscape:transform-center-x=\"2\"\
	transform=\"rotate("+ std::to_string(properties.edges[0].get_gamma(properties.edges[1]) / pi_const * 180) +")\"\n\
	y=\""+ std::to_string(properties.edges[0].y) +"\"\n\
	x=\""+ std::to_string(properties.edges[0].x) +"\"\n\
	height=\"40\"\n\
	width=\"4\"\n\
	id=\"rect2551\"\n\
	style=\"fill:#000000;stroke:#000000;stroke-width:0.564999;stroke-linecap:round;stroke-linejoin:round;paint-order:stroke fill markers\" />\n";		
	}

coordinates wall::closest_point(coordinates c){
	decimal_n minimal_distance = std::numeric_limits<decimal_n>::infinity();
	coordinates *ret;
	for(auto &coo: properties.edges){
		decimal_n current = c.get_distance(coo);
		if(minimal_distance > current){
			minimal_distance = current;
			ret = &coo;
			}
		}
	return *ret;
	};

#endif
