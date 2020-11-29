/*
 * logic.hpp
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


#ifndef LOGIC_HPP
#define LOGIC_HPP

class logic
{	
	// properties of a vehicle
	node 		main_rotation; 
	speeds 		main_speeds;	
	tank 		main_tank;
	location 	main_location;
	
	// map & planning stuff
	map 		main_map;
	
	public:
		logic();
		void init();
		
	private:
		/* add your private declarations */
};

#endif /* LOGIC_HPP */ 