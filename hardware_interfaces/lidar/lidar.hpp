/*
 * lidar.hpp
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


#ifndef LIDAR_HPP
#define LIDAR_HPP

#include <vector>
#include <chrono>
#include <map>

#include "../serial/serial_peripheral.hpp"
#include "../../utils/data_containers/angles/angles/angles.hpp" // and more angles
#include "../../defines/typedefines.h"


class lidar: public serial_peripheral {
	public:
		//~ using serial_peripheral::operator=;
		unsigned_b queue = 0;
		uint8_t convert: 1; // please to convert what he captured
		
		
		enum kinds: uint8_t {
			SND_LDR =		0, /* Send lidar data */
			DND_UND =		6, /* Didn't understand */
			};
		
		struct value_sh {				// 38 bits, round to 40
			unsigned distance 	:13;	// 80 - 8000 mm
			unsigned angle		:9;		// 0-359
			unsigned age		:16; 	// 65.5 secs
			};
			
		struct value_time {				// 38 bits, round to 40
			unsigned distance 	:13;	// 80 - 8000 mm
			unsigned angle		:9;		// 0-359
			steady time; // time of capture by program
			};
			
		struct {
			unsigned first_index:	9;
			unsigned last_index:	9;
			unsigned span:			4; // try to select only every n-t    h value
			unsigned tolerable_age:	9;
			} presets;
			
		std::vector<lidar::value_time> conv_vals; // timestamped 
		const static std::map<uint8_t, std::vector<uint8_t>> table;
		decimal_n range;
		angles * sight;
		chat * _conn;
		lidar(decimal_n rng = 170 /* cm */);
		lidar(chat *c, decimal_n rng = 170 /* cm */);
		lidar(chat &c, decimal_n rng = 170 /* cm */);
		
		void run();
		void question();
		void answer();
		void decode();
		void encode();
		void update();
	private:
		/* add your private declarations */
};

const std::map<uint8_t, std::vector<uint8_t>> lidar::table = {{lidar::SND_LDR, {lidar::SND_LDR}}, 
															  {lidar::DND_UND, {lidar::DND_UND}},};

#endif /* LIDAR_HPP */ 
