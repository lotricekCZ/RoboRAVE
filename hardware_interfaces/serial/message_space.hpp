/*
 * message.cpp
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


#include "message_standard.hpp"
#include "message.hpp"

#ifndef MESSAGE_SPACE_HPP
#define MESSAGE_SPACE_HPP

namespace data{
	namespace send{		
		struct motor{
			uint16_t left_steps;
			uint16_t right_steps; // 4b
			unsigned left_mcrs_hi:14;
			unsigned right_mcrs_hi:14;
			unsigned left_mcrs_lo:14;
			unsigned right_mcrs_lo:14;	//	11b
			unsigned right_unchainer:2;
			unsigned left_unchainer:2;
			unsigned left_dir:2;
			unsigned right_dir:2; // 12b
			unsigned left_erase:1;
			unsigned right_erase:1;
			unsigned input_type:6; // 13b
			};
	
		typedef struct sensor{
			uint16_t period = 0;
			unsigned oversampling:5;
			uint16_t expo_time = 0;	
			};
		
		void translate_sensor(uint8_t &out[16], sensor in){
			out[0] = in.period >> 8 	& 255;
			out[1] = in.period			& 255;
			out[2] = in.oversampling	& 31;
			out[3] = in.expo_time >> 8	& 255;
			out[4] = in.expo_time		& 255;
			}
			
		void translate_motor(uint8_t &out[16], motor in){
			out[0] = motor.left_steps >> 8;
			out[1] = motor.left_steps;
			out[2] = motor.right_steps >> 8;
			out[3] = motor.right_steps;
			
			out[4] = motor.left_mcrs_hi >> 8;
			out[5] = motor.left_mcrs_hi << 2 | motor.left_dir;
			
			out[6] = motor.right_mcrs_hi >> 8;
			out[7] = motor.right_mcrs_hi << 2 | motor.right_dir;
			
			out[8] = motor.left_mcrs_lo >> 8;
			out[9] = motor.left_mcrs_lo << 2 | motor.left_unchainer; 
			out[10] = motor.right_mcrs_lo >> 8;
			out[11] = motor.right_mcrs_lo << 2 | motor.right_unchainer;
			out[12] = (motor.input_type << 2) | (motor.right_erase << 1) | motor.left_erase;
			}
	
	};

};

class message_space{
	message_space(){}
	static virtual void fill_message_space(uint8_t &in[16], speeds);
};

#endif
