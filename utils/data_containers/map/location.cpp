/*
 * location.cpp
 * 
 * Copyright 2020 Jakub Ramašeuski <jakub@jakub-ThinkPad-X250>
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


#include "location.hpp"


location::location()
{
	
}

location::location(decimal_n x, decimal_n y){
	_coordinates.x = x;
	_coordinates.y = y;
	}

location::location(decimal_n x, decimal_n y, uint8_t t){
	_coordinates.x = x;
	_coordinates.y = y;
	set_point(t);
	}
	
location::location(decimal_n x, decimal_n y, type t){
	_coordinates.x = x;
	_coordinates.y = y;
	set_point(t);
	}

location::location(coordinates coo){
	 _coordinates = coo;
	}

decimal_n location::get_distance(location _loc){
	return get_distance(_loc._coordinates.x, _loc._coordinates.y);
	}
	
decimal_n location::get_distance(coordinates _coo){
	return get_distance(_coo.x, _coo.y);
	}
	
decimal_n location::get_distance(decimal_n x, decimal_n y){
	return sqrt(pow(x - _coordinates.x, 2) + pow(y - _coordinates.y, 2));
	}

void location::set_interest(decimal_n in){
	//~ std::cout << "autistrest: " << in << '\n';
	classification.interest_level = in;
	}
	
void location::set_point(uint8_t in){
	classification.point_type = in;
	}

signed_b location::get_interest(){
	return classification.interest_level;
	} 

uint8_t location::get_point(){
	return classification.point_type;
	}
