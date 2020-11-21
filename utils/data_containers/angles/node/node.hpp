/*
 * node.hpp
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


#ifndef DATA_CONTAINERS_ANGLES_NODE_HPP
#define DATA_CONTAINERS_ANGLES_NODE_HPP

class node
{
	public:
		decimal_n distance;
		unsigned intensity:10;
		decimal_n angle;
		
		node();
		node(decimal_n);
		node(decimal_n, decimal_n);
		node(decimal_n, unsigned_n);
		virtual ~node();
		void set_distance(decimal_n);
		void set_intensity(unsigned_n);
		void set_angle(decimal_n);
		
		decimal_n get_distance();
		unsigned_n get_intensity();
		decimal_n get_angle();
	private:
		/* add your private declarations */
};

#endif /* NODE_HPP */ 
