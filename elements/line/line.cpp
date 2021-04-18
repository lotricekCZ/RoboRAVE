/*
 * line.cpp
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

#include <limits>
#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <inttypes.h>

#include "../../defines/constants.h"
#include "../../utils/data_containers/coordinates/coordinates.cpp"
#include "line.hpp"


#ifndef LINE_CPP
#define LINE_CPP

line::line(coordinates a, coordinates b) {

    // Starting with y = mx we can replace y with (y-y1), m with (y2-y1)/(x2-x1)
    // and x with (x-x1), so we obtain (y-y1) = [(y2-y1)/(x2-x1)](x-x1) and simplify to:
    // x(y1-y2) + y(x2-x1) + (x1y2-y1x2) = 0 and hence we conclude that a = (y1-y2)
    // b = (x2-x1) and c = (x1y2-y1x2)


    this -> a = a.y - b.y;
    this -> b = b.x - a.x;
    this -> c = a.x * b.y - a.y * b.x; // or y1*x2 - x1*y2; for ax + by = c
	}
	
line::line(decimal_n a, decimal_n b, decimal_n c) {
    this -> a = a;
    this -> b = b;
    this -> c = c;
	}

line::line(decimal_n angle){
	this -> a = 1;
	this -> b = atan(angle);
	c = 0;
	}

line::line(decimal_n angle, coordinates c){
	this -> b = 1;
	this -> a = -tan(angle);
	this -> c = -(c.x * this -> a + c.y * this -> b);
	}
	
line::line(decimal_n angle, decimal_n c){
	this -> b = 1;
	this -> a = -tan(angle);
	this -> c = c;
	}	

line::line() {
	}

decimal_n line::get_y(decimal_n x){
	// ax + by + c = 0 -> by = -ax -c ->  y = (-ax -c) / b
	// all these this -> are here just for sure
	// returns infinity if no point for such x
	return  (b != 0)?(-(this -> a)*x - this -> c) / this -> b : std::numeric_limits<float>::infinity();
	}

decimal_n line::get_x(decimal_n y){
	// ax + by + c = 0 -> by = -ax -c ->  x = (-by -c) / a
	// all these this -> are here just for sure
	// returns infinity if no point for such y
	return (b != 0)? (-(this -> b)*y - this -> c) / this -> a : std::numeric_limits<float>::infinity();
	}

line line::operator /(decimal_n d){
	return (d != 0)?(line(this -> a / d, this -> b / d, this -> c / d)) : line(0, 0, 0);
	}
	
line line::make_parallel (coordinates c){
	return line(this -> a, this -> b, -(this -> a * c.x + this -> b * c.y));
	}

std::string line::print (line l){
	return 	std::string(std::to_string(l.a) + "x" +((l.b >= 0)?"+":"") +\
			std::to_string(l.b) + "y"+ ((l.c >= 0)?"+":"") + std::to_string(l.c) + " = 0");
	}
	
std::string line::print (){
	return print(*this);
	}
	 
bool line::on_segment (coordinates on_seg, coordinates a_seg, coordinates b_seg){
	return std::abs((on_seg.get_distance(a_seg) + on_seg.get_distance(b_seg)) - a_seg.get_distance(b_seg)) <= 1e-4;
	}

coordinates line::intersection(line a, line b){
	if((a.b * b.a - b.b * a.a) == 0) return coordinates(std::numeric_limits<float>::infinity(), \
														std::numeric_limits<float>::infinity());
	decimal_n x = (- a.b * b.c + b.b * a.c) / (a.b * b.a - b.b * a.a); 
	// place for wtf, but it should work
	// just believe me, this should be ok
	return coordinates(x, (a.b != 0? a.get_y(x): b.get_y(x)));
	}
	
coordinates line::intersection(line a){
	return intersection(a, *this);
	}

line line::make_perpendicular(coordinates c){
	std::cout << print() << std::endl;
	return line(((std::abs(this -> a) < 1e-3)?(-1):(1)) * this -> b, 
				((std::abs(this -> b) < 1e-3)?(1):(-1)) * this -> a, 
				((std::abs(this -> b) < 1e-3)?(-1):(1)) * this -> a * c.y - ((std::abs(this -> a) < 1e-3)?(-1):(1)) * this -> b * c.x);
					
	}
	
line line::make_perpendicular(){ /// for uses of making distance measurements among two parallel lines
	return line(-b, a, c);
	}


line line::make_axis(line a, line b){
	 /// parallel lines, returns the same with average c
	if((a.b * b.a - b.b * a.a) == 0) return line(a.a, b.b, (a.c+b.c)/2);
	coordinates c = a.intersection(a, b);

	//~ std::cout << c.print() << std::endl;
	decimal_n angle = (a.get_angle() + b.get_angle()) / 2.0;
	return line(angle, c);
	}
	
//~ line line::make_perpendicular(coordinates c){
	//~ return line(this -> b, -this -> a, - (this -> a * c.x + this -> b * c.x));
	//~ }
	
decimal_n line::get_angle(){
	return atan2f(-a, b);
	}
	
decimal_n line::get_angle(line l){
	return get_angle() - l.get_angle();
	}
	
decimal_n line::get_distance(line l, coordinates c){
	return std::abs(l.a * c.x + l.b * c.y + l.c)/(sqrt(pow(l.a, 2) + pow(l.b, 2)));
	}
	
decimal_n line::get_distance(line l){
	line n = make_perpendicular();
	return intersection(*this, n).get_distance(intersection(l, n));
	}
	
decimal_n line::get_distance(line l, line m){
	line n = l.make_perpendicular();
	//~ std::cout << intersection(m, n).print() << std::endl;
	//~ std::cout << intersection(l, n).print() << std::endl;
	//~ std::cout << n.print() << std::endl;
	//~ std::cout << line(intersection(l, n), intersection(m, n)).print() << std::endl;
 	return intersection(m, n).get_distance(intersection(l, n));
	}
	
#endif //LINE_CPP
