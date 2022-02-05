/*
 * perimeter.hpp
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


#ifndef PERIMETER_HPP
#define PERIMETER_HPP
#include <array>
//~ #include <mutex>
//~ #include <thread>



class perimeter {
	public:
		class value {
			public:
				unsigned distance 				:13;
				unsigned quality		 		:8;
				uint64_t last_replaced		 	:26;
				unsigned angle		 			:9;
				value(uint16_t distance = 0, uint8_t quality = 0, 
					uint64_t time = 0, uint16_t angle = 0);
			};
		uint32_t replace_time = 1000; // ms
		std::array<perimeter::value, 360> view;
		perimeter();
		bool replace(perimeter::value v); // true if replaced
		bool replace(uint16_t distance = 0, uint8_t quality = 0, uint64_t time = 0, uint16_t angle = 0); // true if replaced
		
			
	private:
		/* add your private declarations */
};

#endif /* PERIMETER_HPP */ 
