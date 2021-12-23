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
	type = 2;
	first = second = coordinates(0, 0);
	}



vector::vector(decimal_n length, decimal_n theta, bool to_coords){
	first = coordinates(0, 0);
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
	type |= (to_coords << 1) | 1; // you've just entered the start. How dare you not use it
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
	
	type = (to_coords << 1) | first;
	}



std::string vector::print(){
	return "=Vector[" + first.print_geogebra() + ", " + (((type >> 1) & 1)? second.print_geogebra(): coordinates::make_local(second.x, second.y, first).print()) + "]";
	// attention: adding first to second is hardcoded when there is just theta and length.
	// MAY CAUSE PROBLEMS IN THE FUTURE!
	}



vector vector::operator << (const vector& rhs){
	coordinates difference = this -> first - rhs.first; // difference of two origins
	vector diff = rhs; // difference of two origins
	return vector(diff.first + difference, diff.second + difference);
	}



vector vector::operator >> (const coordinates& rhs){
	coordinates difference = (coordinates)rhs - (this -> first); // difference of two origins
	return vector(this -> first + difference, this -> second + difference);
	}



vector vector::operator + (const vector& rhs){
	vector add = (*this << rhs);
	return (*this << vector(this -> first + add.first, this -> second + add.second));
	}



vector vector::operator - (const vector& rhs){
	vector add = (*this << rhs);
	return (*this << vector(this -> first - add.first, this -> second - add.second));
	}



vector vector::operator * (const decimal_n& rhs){
	return vector(this -> first, this -> second * rhs - this -> first, true);
	}



vector vector::operator - (const decimal_n& rhs){
	return this -> extend(this -> length() - rhs);
	}



vector vector::operator + (const decimal_n& rhs){
	return this -> extend(this -> length() + rhs);
	}



vector vector::operator / (const decimal_n& rhs){
	return vector(this -> first, this -> length()/rhs, this -> angle(), true);
	}



coordinates vector::operator <<	(const coordinates& rhs){
	coordinates difference = this -> second - this -> first; // difference of two origins
	coordinates orig = rhs; // difference of two origins
	return orig + difference;
	}



decimal_n vector::length(){
	return (type >> 1)? first.get_distance(second): second.x;
	}



coordinates vector::get_origin(){
	return first;
	}





coordinates vector::get_point(){
	return (((type >> 1) & 1)? second: coordinates::make_local(second.x, second.y, first));
	}



decimal_n vector::angle(){
	return (type >> 1)? first.get_gamma(second): second.y;
	}



vector vector::extend(vector v, decimal_n length){
	return vector(v.first, length, v.angle(), true); // to_coords = true
	}



vector vector::extend(decimal_n length){
	return extend(*this, length);
	}

vector vector::swap(vector v){
	return vector(v.get_point(), v.get_origin());
	}

vector vector::swap(){
	return vector::swap(*this);
	}
