/*
 * turbine.hpp
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


#ifndef TURBINE_HPP
#define TURBINE_HPP

#include <vector>
#include <map>

class turbine: public serial_peripheral{
	public:
		enum stepper_options: uint8_t {
			UP = 		1, 
			DOWN = 		0,
			STALLED = 	2
			};
			
		enum stepper_hold: bool {
			YES = 		1, 
			NO = 		0,
			};
			
		enum turbine_options: uint8_t {
			ON = 			1,
			OFF = 			0,
			CALIBRATING = 	2
			};
						
		enum options_mot: uint8_t {
			srt_t = 0,		// Start turbine
			stp_t = 1,      // Stop turbine
			mov_p = 2,      // Move on position
			mov_s = 3,      // Move by steps
			sen_d = 4,      // Send data
			spd_t = 5,      // Set speed turbine
			spd_m = 6       // Set speed mover
			};
		
		enum options: uint8_t {
			MOV_TRB = 1,	/* move with turbine */
			SRT_TRB = 2,	/* start turbine */
			STP_TRB = 3,	/* stop turbine */
			GTD_TRB = 5,	/* Get data turbine */
			DND_UND = 6,	/* Didn`t understand */
			SET_TRB = 7 	/* Setup turbine */
			};
		
		const static std::map<uint8_t, std::vector<uint8_t>> table;
		
		struct decomposed_data {
			unsigned state_duration: 	14;
			unsigned turbine_steps: 	12;
			unsigned turbine_tilt: 		12; // aktualni natoceni na skale od 0-4095 / 1023
			//zalezitosti turbiny
			turbine::stepper_options stepper_dir;
			uint8_t fan_speed;
			turbine::turbine_options motor_opt;
			
			stepper_hold hold;
			
			unsigned option: 	3;
			unsigned has_data: 	1;
		} data {4096, 0,
				2048, stepper_options::STALLED,
				150, turbine_options::OFF, 
				stepper_hold::NO, (uint8_t)options_mot::stp_t, 0
				};
		
		struct _turbine {
			//zalezitosti pulsu
			uint16_t state_duration: 14;
			unsigned turbine_tilt:12; // aktualni natoceni na skale od 0-4096 
			unsigned turbine_steps:12;
			//zalezitosti turbiny
			turbine::turbine_options motor_option;
			turbine::stepper_options stepper_direction;
			unsigned hold:1;
			unsigned minimum:6;
			unsigned maximum:8;
			unsigned repeatings:6;
			uint32_t warm_up_change;
			uint16_t warm_up_duration;
			};


		chat *_conn;

		turbine();
					
		turbine(chat &c);
					
		turbine(chat *c);

		~turbine();

		//~ bool update();
		//~ std::vector<node> get_data(bool update);
		/** 
		 * Stolen from arduino turbine.h
		void move_stepper_motor();
		void turn_on_turbine();
		void turn_off_turbine();
		void handle_in_background();
		void init_servo();
		void set_steps(uint16_t input);
		void set_direction(stepper_options input);
		*/
		
		void run() override;
		void question() override;
		void answer() override;
		void decode() override;
		void encode() override;
		void update() override;
		
		//~ turbine& operator=(const turbine& rhs);
	private:
		/* add your private declarations */
};

const std::map<uint8_t, std::vector<uint8_t>> turbine::table = {{turbine::MOV_TRB, {turbine::MOV_TRB}},
																{turbine::SRT_TRB, {turbine::SRT_TRB}},
																{turbine::STP_TRB, {turbine::STP_TRB}},
																{turbine::GTD_TRB, {turbine::GTD_TRB}},
																{turbine::SET_TRB, {turbine::SET_TRB}},
																};

#endif /* TURBINE_HPP */ 
