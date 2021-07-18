/*
 * line.hpp
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


#ifndef LINE_HPP
#define LINE_HPP

class line
{
	public:
		// pracuje se s ax + bx + c = 0
		decimal_n a;
		decimal_n b;
		decimal_n c;
		decimal_n get_x(decimal_n);
		decimal_n get_y(decimal_n);
		decimal_n get_angle();
		decimal_n get_angle(line);
		static decimal_n get_angle(line, line);
		static decimal_n get_distance(line, coordinates);
		decimal_n get_distance(coordinates);
		decimal_n get_distance(line);
		static decimal_n get_distance(line, line);
		
		line();
		line(coordinates, coordinates);
		line(decimal_n, decimal_n, decimal_n);
		line(decimal_n); // used to create line based on angle in RADIANS against plane
		line(decimal_n, coordinates); // used to create line based on angle in RADIANS against plane
		line(decimal_n, decimal_n); // used to create line based on angle in RADIANS against plane
		
		line make_parallel(coordinates);
		line make_perpendicular(coordinates);
		line make_perpendicular();
		static line make_axis(line, line);
		std::string print(line);
		std::string print();
		
		
		static bool on_segment(coordinates, coordinates, coordinates);
		line operator /(decimal_n);
		static coordinates intersection(line, line);
		coordinates intersection(line);
	private:
		/* add your private declarations */
};

#endif /* LINE_HPP */ 
