/*
 * obstacle.cpp
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


#include "circle.hpp"

#ifndef CIRCLE_CPP
#define CIRCLE_CPP

circle::circle()
{
	
}

bool circle::inside(coordinates a){
	return inside(a.x, a.y);
	}
	
bool circle::inside(decimal_n x, decimal_n y){
	return pow(x - center.x, 2) + pow(y - center.y, 2) <= pow(radius_c, 2);
	}
	
std::vector<coordinates> circle::points(){
	return std::vector<coordinates>();
	}
	
bool circle::is_collision_course(){
	return true;
	}
	

#endif
