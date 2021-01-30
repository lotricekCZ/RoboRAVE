/*
 * angles.hpp
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


#ifndef ANGLES_ANGLES_HPP
#define ANGLES_ANGLES_HPP

#include <vector>
#include "../node/node.cpp"

class angles: public std::vector<node>
{
	public:
		using std::vector<node>::push_back;
		using std::vector<node>::pop_back;
	    using std::vector<node>::operator[];
	    using std::vector<node>::begin;
	    using std::vector<node>::erase;
	    using std::vector<node>::end;
	    using std::vector<node>::at;
		angles();
		virtual ~angles();
		node get_angle(signed_n);
		angles load_virtual(coordinates, map &m);
		angles load_virtual_circular(coordinates, map &m, decimal_n, decimal_n, decimal_n);
		
	private:
		/* add your private declarations */
};

#endif /* ANGLES_HPP */ 
