/*
 * vector.hpp
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

#include <variant>
//~ #include <vector>
#include "../../defines/typedefines.h"
#include "../../utils/data_containers/coordinates/coordinates.hpp"

#ifndef VECTOR_HPP
#define VECTOR_HPP

class vector {
	public:
		// constructors
		vector(); // defaultly zero-length
		vector(decimal_n length, decimal_n theta, bool to_coords = false);
		
		vector(coordinates start, decimal_n length, decimal_n theta, 
				bool to_coords = false);
				
		vector(coordinates start, coordinates end, 
				bool to_coords = true, 
				bool first = true);
		// functions
		decimal_n length();
		std::string print();
		static coordinates move(vector, coordinates);
		
		vector operator +	(const vector& rhs);
		vector operator -	(const vector& rhs);
		
		vector operator <<	(const vector& rhs); // move rhs origin to lhs
		vector operator >>	(const coordinates& rhs); // move rhs origin to lhs
		
		vector operator /	(const decimal_n& rhs);
		vector operator -	(const decimal_n& rhs); // subtracts the value from vector length
		vector operator *	(const decimal_n& rhs);
		
		coordinates operator <<	(const coordinates& rhs); // shifts the coordinate according to the vector
	private:
		coordinates first; 
		/* first parameter, can be [x; y] when the location of point matters type(0-1), 
		 * or will be [0; 0] when it matters type(2-3) 
		 * */
		coordinates second; 
		unsigned type:	2;
		/* 
		 * bit 0 - first coordinates:	matters(1)
		 *								doesn't(0)
		 * bit 1 - second coordinates:	is coordinate	 (1)
		 *								is length + theta(0)
		 * */
		/* add your private declarations */
};



#endif /* VECTOR_HPP */ 
