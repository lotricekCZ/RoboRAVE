/*
 * step.hpp
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

//~ #include "../../data_containers/speeds/speeds.cpp"
//~ #include "../../data_containers/coordinates/coordinates.cpp"
//~ #include "../../data_containers/map/map.cpp"
#include "../../../elements/circle/circle.cpp"
#include "../../../elements/line/line.cpp"
#include <limits>
#include <variant>

#ifndef STEP_HPP
#define STEP_HPP

class step
{
	public:
	speeds v;
	
	coordinates start;
	coordinates end;
	
	std::variant<circle, line> formula;
	enum equation_type{
		line_e = 0,
		circle_e = 1
		};
	equation_type _type;
	
	decimal_n time;
	
	decimal_n time_start; 	// time when the movement started
	
	decimal_n angle_start; 	// angle when the movement started
	decimal_n angle_end; 	// angle when the movement is going to end
	
	decimal_n omega;		// angle which is driven in one second
	decimal_n phi; 			// total angle which is driven
	
	public:
		//~ step(speeds, coordinates, coordinates, coordinates, decimal_n, decimal_n, decimal_n, decimal_n);step(speeds, coordinates, coordinates, coordinates, decimal_n, decimal_n, decimal_n, decimal_n);
		step(coordinates, coordinates, coordinates);
		step(coordinates, coordinates);
		step();
		std::string inkscape_print();
			
	private:
		/* add your private declarations */
};

#endif /* STEP_HPP */ 
