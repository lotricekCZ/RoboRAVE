/*
 * coordinates.cpp
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

#include "../../../defines/constants.h"
#include "coordinates.h"



coordinates::coordinates()
{
	
}

coordinates::coordinates(decimal_n x, decimal_n y)
{
	this -> x = x;
	this -> y = y;
}

coordinates coordinates::make_local(coordinates abs, coordinates rel, decimal_n ang){
	decimal_n distance = get_distance(rel.x, rel.y);
	decimal_n gamma = get_gamma(rel.x, rel.y);
	uint8_t dec = get_dec(rel.x, rel.y);
	return coordinates(abs.x + get_rel_x(ang, gamma, distance, dec), abs.y + get_rel_y(ang, gamma, distance, dec));
	}

/*
 * 
 * name: coordinates::make_local
 * @param abs: absolute coordinates on a map
 * @param distance: distance to that point
 * @param angle: absolute angle at which beam measured such distance, RADIANS
 * @return
 * 
 */

coordinates coordinates::make_local(coordinates abs, decimal_n distance, decimal_n ang){
	
	uint8_t dec = get_dec(0,0);
	//~ decimal_n gamma = ;
	return coordinates(abs.x + get_rel_x(ang, pi/4.0, distance, dec), abs.y + get_rel_y(ang, pi/4.0, distance, dec));
	}

decimal_n coordinates::get_gamma(decimal_n x_rel, decimal_n y_rel){
	return atan((decimal_n)y_rel / (decimal_n)x_rel);
	}
	
decimal_n coordinates::get_distance(decimal_n x_rel, decimal_n y_rel){
	return sqrt(pow(x_rel-this->x, 2) + pow(y_rel-this->y, 2));
	}

decimal_n coordinates::get_distance(coordinates c){
	return get_distance(c.x, c.y);
	}


decimal_n coordinates::get_rel_x(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec){
	return -1*(((dec >> 1) & 1? 1 : -1))*cos((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}

decimal_n coordinates::get_rel_y(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec){
	return -1*(((dec >> 1) & 1? 1 : -1))*sin((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}
	
uint8_t coordinates::get_dec(decimal_n x_rel, decimal_n y_rel){
	return (uint8_t) ((x_rel > 0) | (((x_rel < 0) & (y_rel > 0)) | ((x_rel > 0) && (y_rel < 0))));
	}
	
