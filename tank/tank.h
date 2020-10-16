/*
 * tank.h
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

#ifndef TANK_TANK_H
#define TANK_TANK_H

#include <pthread.h>
#include <math.h>
#include <iostream>
#include <future>
#include <thread>


#ifndef decimal_n
	#define decimal_n float
#endif

#ifndef signed_n
	#include <inttypes.h>
	#define signed_n int16_t
#endif

#ifndef unsigned_n
	#include <inttypes.h>
	#define unsigned_n uint16_t
#endif

class tank{
	public:
		decimal_n joystick_range = 100; // default joystick range
		decimal_n speeds[2] = {0, 0};
		void assign_speeds(decimal_n x_rel, decimal_n y_rel){
			auto V = std::async(&tank::get_velocity, this, -1*x_rel, y_rel);
			auto W = std::async(&tank::get_omega, this, -1*x_rel, y_rel);
			
			decimal_n velocity = V.get();
			decimal_n omega = W.get();
			
			auto right = std::async(&tank::get_side_v, this, omega, velocity, 1);
			auto left = std::async(&tank::get_side_v, this, omega, velocity, 0);
			speeds[0] = left.get();
			speeds[1] = right.get();
			std::cout << "result: ["<< speeds[0] << ", " << speeds[1] << "]\n" << std::endl;
			}
		decimal_n get_side_v(decimal_n omega, decimal_n velocity, bool sig){
			return (velocity + (sig? 1: -1) * omega) / 2; 
			}
		
		
		decimal_n get_omega(decimal_n x, decimal_n y){
			return ((decimal_n)joystick_range - abs((decimal_n)y)) * ((decimal_n)x / (decimal_n)joystick_range) + (decimal_n)x;
			}
			
		decimal_n get_velocity(decimal_n x, decimal_n y){
			return ((decimal_n)joystick_range - abs((decimal_n)x)) * ((decimal_n)y / (decimal_n)joystick_range) + (decimal_n)y;
			}
	
	};

#endif // TANK_TANK_H

