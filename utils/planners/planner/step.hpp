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


#ifndef STEP_HPP
#define STEP_HPP

class step
{
	public:
	speeds v;
	enum direction:bool{left = 0, right = 1};
	coordinates start;
	coordinates end;
	bool direction_curve;
	std::variant<circle, line> formula;
	enum equation_type: bool{
		line_e = 0,
		circle_e = 1
		};
	equation_type _type;
	decimal_n time;
	
	decimal_n time_start; 	// time when the movement started
	
	decimal_n angle_start; 	// angle when the movement started
	decimal_n angle_end; 	// angle when the movement is going to end
	
	decimal_n omega;		// angle which is driven in one second
	decimal_n phi; 			// total angle which is driven, can be also negative
	
	public:
		//~ step(speeds, coordinates, coordinates, coordinates, decimal_n, decimal_n, decimal_n, decimal_n);step(speeds, coordinates, coordinates, coordinates, decimal_n, decimal_n, decimal_n, decimal_n);
		step(coordinates, coordinates, coordinates, bool is_right = direction::right, bool compute_angle = true);
		step(coordinates, coordinates, bool compute_angle = true);
		step();
		bool on_segment_circular(coordinates point);
		bool on_segment_linear(coordinates point);
		static std::pair<step, step> get_perimeters(step, decimal_n perimeter = properties::widths::robot / 2);
		std::string print();
		std::string print_inkscape();
		std::string print_geogebra();
		
		static std::vector<coordinates> intersection(step a, step b);
		static std::vector<coordinates> intersection(step s, circle c);
		static std::vector<coordinates> intersection(step s, line l);
		
		std::vector<coordinates> intersection(step b);
		std::vector<coordinates> intersection(circle c);
		std::vector<coordinates> intersection(line l);
		
		static decimal_n get_distance(step s, coordinates c, bool carry_caps = true);
	private:
		/* add your private declarations */
};

#endif /* STEP_HPP */ 
