/*
 * triangle.hpp
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

 
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "../../defines/typedefines.h"

class triangle
{
	public:
		coordinates a, b, c;
		decimal_n len_a = 0, len_b = 0, len_c = 0;
		triangle(location, location, location);
		triangle(coordinates, coordinates, coordinates);
		decimal_n herone_s();
		decimal_n length();
		~triangle();
	private:
		/* add your private declarations */
};

#endif /* TRIANGLE_HPP */ 
