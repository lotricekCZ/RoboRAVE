/*
 * motors.hpp
 * 
 * Copyright 2021 Jakub Ramašeuski <jakub@skaryna.net>
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


#ifndef MOTORS_HPP
#define MOTORS_HPP

#include <vector>
#include <array>
#include <map>

class motors: public serial_peripheral{
	public:
		unsigned_b queue = 0;
		enum direction: uint8_t {
			FRONT = 	0, 
			BACK = 		1, 
			STALLED = 	2
			};
		
		enum state: uint8_t {
			ON = 		2,
			OFF = 		0,
			BUFFER = 	1
			};
			
		enum kinds: uint8_t {
			SET_MOT = 0,	/* Set motor */
			GTD_MOT = 4,	/* Get data motor */
			DND_UND = 6,	/* Didn`t understand */
			};
		
		/* R = right (0), L = left (1)
		 * 
		 * R = rewrite (3)
		 * I = pulse length set (speed manipulation) (2)
		 * D = direction set (4)
		 * C = chaining set (5)
		 * */
		unsigned erase_flags: 6;
		
		const static std::map<uint8_t, std::vector<uint8_t>> table;
		
		struct decomposed_data {
			uint16_t left_steps;
			uint16_t right_steps; // 4b
			unsigned left_mcrs_hi:		14;
			unsigned right_mcrs_hi:		14;
			unsigned left_mcrs_lo:		14;
			unsigned right_mcrs_lo:		14;     
			unsigned right_unchainer:	2;
			unsigned left_unchainer:	2;
			unsigned left_dir:			2;
			unsigned right_dir:			2; // 12b
			unsigned left_erase:		1;
			unsigned right_erase:		1;
			unsigned input_type:		6; // 13b
		} data {0, 0,
				16000, 16000,
				16000, 16000,
				state::BUFFER, state::BUFFER,
				direction::FRONT, direction::FRONT,
				1, 1, 0
				};
		
		struct motor {
			//kroky
			uint16_t scheduled_steps; // zadany pocet kroku
			uint16_t remaining_steps; // zbyvajici pocet kroku
			uint32_t traveled_steps;
			//intervaly
			unsigned high_interval:	14; // 0 - 2^14-1 us (16383 us)
			unsigned low_interval:	14; // time in us
			unsigned rewrite: 		1;
			motors::direction direction;
			motors::state chain; // moznosti on off a buffer - zapnuto, vypnuto, bere kroky ze zasobniku
			} left, right, left_data, right_data;
		

		chat *_conn;

		motors();
					
		motors(chat &c);
					
		motors(chat *c);

		~motors();

		//~ bool update();
		//~ std::vector<node> get_data(bool update);
		void run() override;
		void question() override;
		void answer() override;
		void decode() override;
		void encode() override;
		void update() override;
		bool assign(std::array<motors::motor, 2> in, uint8_t status);
		
		//~ motors& operator=(const motors& rhs);
	private:
		/* add your private declarations */
};

const std::map<uint8_t, std::vector<uint8_t>> motors::table = {{motors::SET_MOT, {motors::SET_MOT}},
																{motors::GTD_MOT, {motors::GTD_MOT}},
																{motors::DND_UND, {motors::DND_UND}},
																};

#endif /* motors_HPP */ 
