/*
 * translator_lidar.hpp
 * 
 * Copyright 2022 Jakub Ramašeuski <jakub@skaryna.net>
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

#include "../lidar/lidar.cpp"

#ifndef TRANSLATOR_LIDAR_HPP
#define TRANSLATOR_LIDAR_HPP

class translator_lidar{
	public:
		struct {
			unsigned first_index:	9;
			unsigned last_index:	9;
			unsigned span:			4; // try to select only every n-th value
			unsigned current_index:	9;
			unsigned tolerable_age:	9;
		} presets;
		
		struct value_sh {				// 38 bits, round to 40
			unsigned distance 	:13;	// 80 - 8000 mm
			unsigned angle		:9;		// 0-359
			unsigned age		:16; 	// 65.5 secs
			};
			
		translator_lidar();
		uint8_t data[16];
		lidar *main_lidar;
		void decompose(uint8_t in[16]);
		bool compose();
		bool is_longer();
			
	private:
		/* add your private declarations */
};

#endif /* TRANSLATOR_LIDAR_HPP */ 
