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
#include <vector>
#include <cmath>
#include <string>
#include "coordinates.h"

#ifndef COORDINATES_CPP
#define COORDINATES_CPP

coordinates::coordinates()
{
	
}

coordinates::coordinates(decimal_n x, decimal_n y)
{
	this -> x = x;
	this -> y = y;
}


/*
 * 
 * name: coordinates::make_local
 * @param abs: absolute coordinates on a map
 * @param rel: coordinates to be transformed to local
 * @param alpha: uhel, kterym robot na abs stoji, RADIANS
 * @return lokalni souradnice bodu abs z bodu rel(jimz je napr robot) pod uhlem alpha 
 * 
 */

coordinates coordinates::make_local(coordinates abs, coordinates rel, decimal_n alpha){
	coordinates c = make_rotation(abs - rel, alpha - pi_const/2);
	return c;
	}
	
/*
 * 
 * name: coordinates::make_local
 * @param abs: absolute coordinates on a map
 * @param alpha: uhel, kterym robot na abs stoji, RADIANS
 * @return lokalni souradnice bodu abs z bodu rel(jimz je napr robot) pod uhlem alpha 
 * 
 */

coordinates coordinates::make_local(coordinates abs, decimal_n alpha){
	return make_local(abs, (*this), alpha);
	}

/*
 * 
 * name: coordinates::make_local
 * @param distance: coordinates to be transformed to local
 * @param alpha: uhel, pod kterym byla vzdalenost namerena vuci ose y, RADIANS
 * @return lokalni souradnice bodu rel daneho uhlu a vzdalenosti
 * 
 */

coordinates coordinates::make_local(decimal_n distance, decimal_n ang){
	return coordinates(distance * cos(ang), distance * sin(ang));
	}

/*
 * 
 * name: coordinates::make_global
 * @param abs: absolute coordinates on a map
 * @param distance: distance to that point
 * @param angle: absolute angle at which beam measured such distance, RADIANS
 * @return globalni souradnice bodu z bodu abs(jimz je napr robot), vuci nemuz jsme takto vzdaleni a pod timto uhlem
 * 
 */
	
coordinates coordinates::make_global(coordinates abs, coordinates rel, decimal_n alpha){
	coordinates c = make_rotation(rel, alpha + pi_const/2);
	return abs + c;
	}
	
coordinates coordinates::make_global(coordinates rel, decimal_n alpha){
	return make_global(*this, rel, alpha);
	}
	
coordinates coordinates::make_rotation(coordinates rel, decimal_n alpha){
	return coordinates(rel.x * cos(alpha) - (rel.y * sin(alpha)), rel.x * sin(alpha) + (rel.y * cos(alpha)));
	}

coordinates coordinates::get_closest(std::vector<coordinates> &c){
	if(c.size() == 0){return coordinates(std::numeric_limits<decimal_n>::infinity(), 
										 std::numeric_limits<decimal_n>::infinity());
					}
	decimal_n shortest = std::numeric_limits<decimal_n>::infinity();
	coordinates* closest;
	decimal_n curr;
	for(auto &s: c){
		curr = this -> get_distance(s);
		if(shortest > curr){
			shortest = curr;
			closest = &s;
			}
		}
	return *closest;
	}
	
coordinates coordinates::get_closest(std::vector<coordinates> c){
	if(c.size() == 0){return coordinates(std::numeric_limits<decimal_n>::infinity(), 
										 std::numeric_limits<decimal_n>::infinity());
					}
	decimal_n shortest = std::numeric_limits<decimal_n>::infinity();
	coordinates* closest;
	decimal_n curr;
	for(auto &s: c){
		curr = this -> get_distance(s);
		if(shortest > curr){
			shortest = curr;
			closest = &s;
			}
		}
	return *closest;
	}

decimal_n coordinates::get_gamma(decimal_n x_rel, decimal_n y_rel){
	return ((y_rel < 0)? 2 * pi_const : 0 ) + atan2((decimal_n)y_rel, (decimal_n)x_rel);
	}
	
decimal_n coordinates::get_gamma(coordinates c){
	return get_gamma(c.x - x, c.y - y);
	}
	
decimal_n coordinates::get_distance(decimal_n x_rel, decimal_n y_rel){
	return sqrt(pow(x_rel-this->x, 2) + pow(y_rel-this->y, 2));
	}

bool coordinates::is_invalid(){
	return *this == coordinates(std::numeric_limits<decimal_n>::infinity(), 
								std::numeric_limits<decimal_n>::infinity());
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
	return (uint8_t) ((x_rel > 0) | (((x_rel < 0) & (y_rel > 0)) | ((x_rel > 0) && (y_rel < 0))) );
	}
	
std::string coordinates::print(){
	//~ return std::string("["+ std::to_string(x) +"; "+ std::to_string(y) +"]");
	return std::string("("+ std::to_string(x) +", "+ std::to_string(y) +")");
	}

#endif
