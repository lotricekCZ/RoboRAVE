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
		
		line();
		line(coordinates, coordinates);
		line(decimal_n, decimal_n, decimal_n);
		
		line operator /(decimal_n);
		coordinates intersection(line, line);
	private:
		/* add your private declarations */
};

#endif /* LINE_HPP */ 