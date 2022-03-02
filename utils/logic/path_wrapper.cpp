/*
 * path_wrapper.cpp
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


#include "path_wrapper.hpp"
#include "../../elements/vector/vector.hpp"

typedef vector col_v;

path_wrapper::path_wrapper(std::vector<step> copy, bool start, bool end): path(copy, start, end) {
	
	}



path_wrapper::path_wrapper(const path& copy): path(copy) {
	
	}



path_wrapper::path_wrapper(step copy, bool start, bool end, bool complete): path(copy, start, end, complete) {
	
	}



std::pair<uint8_t, std::array<motors::motor, 2>> path_wrapper::translate(){
	std::array<motors::motor, 2> ret;
	uint8_t status = 0;
	switch(this -> at(head)._type){
		case step::circle_e: {
			break;
			}
			
		case step::line_e: {
			decimal_n min_speed = std::max(variables::limits::minimal::wheel_velocity, std::min(now_speeds.left, now_speeds.right)); 
			// Only place where going back is used when retracting (hopefully)
			decimal_n length = this -> at(head).length();
			decimal_n time = length / min_speed;
			
			if(time >= variables::step::acceleration_time){
				coordinates inter = col_v(this -> at(head).start, 
							min_speed * variables::step::acceleration_time, 
							(this -> at(head).start.get_gamma(this -> at(head).end)), 1).get_point();
				this -> insert(this -> begin() + (head), step(this -> at(head).start, inter));
				this -> at(head + 1) = step(inter, this -> at(head + 1).end);
				status = 0b11111;
				}
			//~ ret.at(0).scheduled_steps = ret.at(1).scheduled_steps = 
			break;
			}
		}
	return std::make_pair(status, ret);
	}



decimal_n path_wrapper::get_velocity(decimal_n x){ // sigmoid is used in these calculations
	// (top_speed - low_speed) / (1 + (acceleration_const + x^2)^(-(x - offset))) + low_speed
	constexpr unsigned_b acceleration_const = 128;
	constexpr decimal_n offset = 0.9;
	
	return (variables::limits::maximal::wheel_velocity - variables::limits::minimal::wheel_velocity)
			/ std::pow((1 + (acceleration_const + std::pow(x, 2))), (-(x - offset))) + variables::limits::minimal::wheel_velocity;
	}
