/*
 * vector.cpp
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


#include "vector.hpp"


vector::vector(){
	
	}

vector::vector(decimal_n length, decimal_n theta, bool to_coords){
	if(to_coords){
		second = coordinates::make_local(length, theta);
		} else {
			second.x = length;
			second.y = theta;
			}
	type |= to_coords << 1;
	}

vector::vector(coordinates start, decimal_n length, decimal_n theta, bool to_coords){
	if(to_coords){
		second = coordinates::make_local(length, theta, start);
		} else {
			second.x = length;
			second.y = theta;
			}
	
	first = start;
	type |= to_coords << 1 | 1; // you've just entered the start. How dare you not use it
	}

vector::vector(coordinates start, coordinates end, bool to_coords, bool first){
	if(to_coords){
		this -> first = start;
		this -> second = end;
		if(!first){
			this -> first = this -> first - start;
			this -> second = this -> second - start;
			}
		} else {
			this -> second.x = start.get_distance(end);
			this -> second.y = start.get_gamma(end);
			this -> first = (!first)? start : coordinates(0, 0);
			}
	
	type = to_coords << 1 | first;
	}

std::string vector::print(){
	return "=Vector[" + first.print_geogebra() + ", " + second.print_geogebra() + "]";
	}
