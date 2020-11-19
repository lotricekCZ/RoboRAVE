/*
 * triangle.cpp
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


#include "triangle.hpp"


triangle::triangle(location a, location b, location c)
{
	this -> a = a._coordinates;
	this -> b = b._coordinates;
	this -> c = c._coordinates;
	length();
}

triangle::triangle(coordinates a, coordinates b, coordinates c)
{
	this -> a = a;
	this -> b = b;
	this -> c = c;
	length();
}

decimal_n triangle::herone_s(){
	decimal_n s = (length())/2.0f;
	return sqrt(s*(s - len_a) * (s - len_b) * (s - len_c));
	}
	
decimal_n triangle::length(){
	len_c = sqrt(pow((a.x - b.x), 2.0f) + pow((a.y - b.y), 2.0f)); 
	len_a = sqrt(pow((c.x - b.x), 2.0f) + pow((c.y - b.y), 2.0f)); 
	len_b = sqrt(pow((a.x - c.x), 2.0f) + pow((a.y - c.y), 2.0f));
	return len_a + len_b + len_c;
	}

triangle::~triangle(){}
