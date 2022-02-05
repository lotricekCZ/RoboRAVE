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


class lidar {
	struct message {
		uint8_t start[ldr_std::length_header];
		uint16_t speed;
		uint16_t angle_start;
		perimeter::value nodes[ldr_std::dist_num];
		uint16_t angle_end;
		uint16_t unknown;
		};
	uint8_t buffer[ldr_std::length_packet];
	uint8_t index = 0;
	uint8_t index_message = 0;
	public:
		enum loop_ret: uint8_t {
			OK = 			0b0,	// SUCCESS of mentioned activities
			FAIL = 			0b1,	// FAIL of mentioned activities
			NEW_PACKET = 	0b10,	// ACTIVITY: update perimeter
			OPEN_S = 		0b100,	// ACTIVITY: Serial open
			};
		HardwareSerial *attached = &Serial1;
		perimeter _perimeter;
		uint32_t baud: 		18;
		unsigned started: 1;
		float Hz = 0;
		
		lidar();
		bool read();
		//~ bool parse(uint8_t *bytes[ldr_std::length_packet]);
		bool parse(uint8_t *bytes[ldr_std::length_packet]);
		bool parse();
		void attach(HardwareSerial *port);
		//~ lidar::loop_ret handle_in_background();
		lidar::loop_ret handle_in_background();
		
			
	private:
		/* add your private declarations */
};

#endif /* LIDAR_HPP */ 
