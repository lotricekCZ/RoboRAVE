/*
 * circle.hpp
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


#ifndef CIRCLE_HPP
#define CIRCLE_HPP

class circle{
	public:
		decimal_n radius = 1;
		coordinates center;
		circle(coordinates, decimal_n);
		circle(decimal_n, decimal_n, decimal_n);
		bool inside(coordinates a);
		bool inside(decimal_n x, decimal_n y);
		std::vector<coordinates> points();
		std::vector<coordinates> intersection(line, circle); // function to decide if sth intersects
		std::vector<coordinates> intersection(circle k, circle c);
		
		void circle_tangents(coordinates c, decimal_n r1, decimal_n r2, std::vector<line> & ans);
		std::vector<line> circle_tangents(circle a, circle b);
		std::string print();
		
		inline bool operator==(const circle& rhs){ 
			return this -> center == rhs.center && this -> radius == rhs.radius;
			}
	private:
		/* add your private declarations */
};

#endif /* OBSTACLE_HPP */ 
