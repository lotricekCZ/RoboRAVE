/*
 * location.hpp
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

#include <inttypes.h>
#include <cmath>

#include "../../../defines/constants.h"
#include "../coordinates/coordinates.hpp"

#ifndef LOCATION_HPP
#define LOCATION_HPP

#define LOCATION_PT_S 5 // size of point type in location class 


	 
class location
{
	public:
	enum type: uint8_t {
		_unknown = 			0b0, 	// presetted points in grid generated by map which must be discovered
		_barrier =		 	0b1,	/*	obstacle on the track */
		_barrier_p =		0b10,	/*	predicted obstacle on the track */
		_candle = 			0b11,	/*	candle that has been found */
		_candle_blown = 	0b100,	/*	target that has been found and eliminated */
		_out_of_map = 		0b101,	/* 	objects detected and assigned 
										by any sensor and then 
										found out to be  out of the map. */
		_line_border = 		0b110,	/*	cara, ktera nesmi byt prejeta pro zustani ve hristi */
		_line_surround = 	0b111,  // line surrounding the target
		
		_target = 			0b1000,	/*	bod, na ktery je cestovano */
		_target_old = 		0b1001, // target set previously
		_target_check = 	0b1010, // target checkpoints - points that lead to target
		_origin = 			0b1011, // [0, 0] 
		_corner = 			0b1100, 
		_interesting = 		0b1101, 	// point that is interesting due some obstacles or strange consistency
		_discovered = 		0b1110, 	// place that was discovered.
		_boring = 			0b1111 	// place that was discovered and has no usage.
	 };
	 
	
		location();
		location(decimal_n, decimal_n);
		location(coordinates);
		location(coordinates, uint8_t);
		location(coordinates, location::type);
		location(decimal_n, decimal_n, uint8_t);
		location(decimal_n, decimal_n, location::type);
		
		decimal_n get_distance(location);
		decimal_n get_distance(coordinates);
		decimal_n get_distance(decimal_n, decimal_n);
		
		decimal_n get_angle(location);
		decimal_n get_angle(coordinates);
		decimal_n get_angle(decimal_n, decimal_n);
		
		
		void set_interest(decimal_n); 
		void set_point(uint8_t);
		void set_point(type);
		
		signed_b get_interest(); 
		uint8_t get_point();
		
		coordinates _coordinates;
		
		struct {
			struct {
				unsigned distance:1;
				unsigned cam_therm:1;
				unsigned cam:1;
				unsigned sensor_ir:1;
				unsigned sensor_ground:1;
				} exp_level;
			
			unsigned point_type:LOCATION_PT_S;
			signed interest_level:30; 			/* 	level of how much is the point
													interesting and gives us the 
													need and priority of visiting
													the place. Every surrounding _unknown and _interesting 
													and their interests in range 
													is counted into interest level */
			
			} classification;
	private:
		/* add your private declarations */
};

#endif /* MAP_ELEMENT_HPP */ 
