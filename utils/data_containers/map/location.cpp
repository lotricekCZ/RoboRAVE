/*
 * location.cpp
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


#include "location.hpp"
#ifndef LOCATION_CPP
#define LOCATION_CPP

location::location(){
	
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
	
location::location(coordinates coo, type t){
	 _coordinates = coo;
	 set_point(t);
	}
	
location::location(coordinates coo, uint8_t t){
	 _coordinates = coo;
	 set_point(t);
	}

decimal_n location::get_distance(location _loc){
	return get_distance(_loc._coordinates.x, _loc._coordinates.y);
	}
	
decimal_n location::get_distance(coordinates _coo){
	return get_distance(_coo.x, _coo.y);
	}

/**
 * 
 * name: location::get_distance
 * @param x: x coordinate of destination point
 * @param y: y coordinate of destination point
 * 
 * @return distance between the point and the location
 * based on the Pythagorus triangle
 * 
 */

decimal_n location::get_distance(decimal_n x, decimal_n y){
	return std::hypot(x - _coordinates.x, y - _coordinates.y);
	}



decimal_n location::get_angle(location loc){
	return get_angle(loc._coordinates.x, loc._coordinates.y);
	}

decimal_n location::get_angle(coordinates coo){
	return get_angle(coo.x, coo.y);
	}

/**
 * 
 * name: location::get_angle
 * @param x: x coordinate of destination point
 * @param y: y coordinate of destination point
 * 
 * @return angle between the point and the location
 * 
 */
 
decimal_n location::get_angle(decimal_n x, decimal_n y){
	return (((y - _coordinates.y) < 0)? 2 * pi_const: 0) + (atan2(y - _coordinates.y, x - _coordinates.x));
	}



void location::set_interest(decimal_n in){
	//~ std::cout << "autistrest: " << in << '\n';
	classification.interest_level = in;
	}
	
void location::set_point(uint8_t in){
	classification.point_type = in;
	}
	
void location::set_point(type in){
	classification.point_type = in;
	}

signed_b location::get_interest(){
	return classification.interest_level;
	} 

uint8_t location::get_point(){
	return classification.point_type;
	}

#endif // LOCATION_CPP
