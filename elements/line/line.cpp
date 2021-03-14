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
	return coordinates(x, a.get_y(x));
	}

#endif //LINE_CPP
