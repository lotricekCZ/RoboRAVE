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
			remainder = 0;
			break;
			}
			
		case step::line_e: {
			
			decimal_n min_speed = std::max(variables::limits::minimal::wheel_velocity, std::min(now_speeds.left, now_speeds.right)); 
			// Only place where going back is used when retracting (hopefully)
			printf("sp now: %f\n", now_speeds.left);
			printf("sr now: %f\n", now_speeds.right);
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
			
			decimal_n steps = this -> at(head).length() / variables::wheel_step_length_const;
			decimal_n x = get_closest(min_speed) + 0.4;
			x = (x > 3)? 3: (x < 0)? 0: x;
			decimal_n speed = get_velocity(x);
			now_speeds.left = now_speeds.right = speed;
			printf("x: %f\n", x);
			printf("sp: %f\n", now_speeds.left);
			printf("sr: %f\n", now_speeds.right);
			printf("speed: %.4f m/s\n", speed);
			printf("period: %i us\n", now_speeds.to_hw_speed(speed));
			//~ printf("frequency: %.4f s", speed);
			remainder += (steps - std::floor(steps));
			ret.at(0).scheduled_steps = ret.at(1).scheduled_steps = std::floor(steps) + std::floor(remainder);
			ret.at(0).high_interval = ret.at(0).low_interval = 
				ret.at(1).high_interval = ret.at(1).low_interval = std::floor(now_speeds.to_hw_speed(speed));
			printf("period 2: %i s\n", ret.at(0).high_interval);
			remainder -= std::floor(remainder); // this is to assure that not so many steps are lost
			break;
			}
		}
	return std::make_pair(status, ret);
	}



decimal_n path_wrapper::get_velocity(decimal_n x){ // sigmoid is used in these calculations
	// (top_speed - low_speed) / (1 + (acceleration_const + x^2)^(-(x - offset))) + low_speed
	// (0.67 - 0.08) / (1 + (128 + x²)^(-(x - 0.9))) + 0.08
	constexpr unsigned_b acceleration_const = 128;
	constexpr decimal_n offset = 0.9;
	
	return (variables::limits::maximal::wheel_velocity - variables::limits::minimal::wheel_velocity)
			/ (1 + std::pow((((decimal_n)acceleration_const + std::pow(x, 2))), (-x + offset))) + variables::limits::minimal::wheel_velocity;
	}



decimal_n path_wrapper::get_closest(decimal_n x){
	decimal_n ret = 0;
	decimal_n diff = std::numeric_limits<decimal_n>::infinity();
	decimal_n y = get_derivative(x);
	for(uint8_t i = 0; i < 30; i++){
		decimal_n diff_c = std::abs(get_velocity((decimal_n)i / 10.0f) - (y));
		printf("\t%f\n", diff_c);
		if(diff_c < diff){
			diff = diff_c;
			printf("CHANGE %f\t%f\n\n\n", (decimal_n)i / 10.0f, diff_c);
			ret = (decimal_n)i / 10.0f;
			}
		}
	return ret;
	}



decimal_n path_wrapper::get_derivative(decimal_n x){ // derivative of that sigmoid is used in these calculations
	// (top_speed - low_speed) / (1 + (acceleration_const + x^2)^(-(x - offset))) + low_speed
	// (128 + x²)^0.9 (128 + x²)^x (ln(128 + x²) (128 (-0.08 + 0.67) - 0.08x² + 0.67x²) + 0.9 (2 (0.08) x - 2 (0.67) x) - 2 (0.08) x² + 2 (0.67) x²) / (((128 + x²)^0.9)² (128 + x²) + (128 + x²)^0.9 (128 + x²)^x (2 (128) + 2x²) + ((128 + x²)^x)² (128 + x²))
	
	constexpr unsigned_b acceleration_const = 128;
	constexpr decimal_n offset = 0.9;
	// wow, this is a black box!
	return std::pow((acceleration_const + std::pow(x, 2)), offset) 
			* std::pow((acceleration_const + std::pow(x, 2)), x)
			* (
				std::log(acceleration_const + std::pow(x, 2)) 
				* (
					acceleration_const 
						* (
							- variables::limits::minimal::wheel_velocity 
							+ variables::limits::maximal::wheel_velocity
							)
					- variables::limits::minimal::wheel_velocity
						* std::pow(x, 2)
					+ variables::limits::maximal::wheel_velocity 
						* std::pow(x, 2)
					)
				+ offset 
					* (2 
						* (
							variables::limits::minimal::wheel_velocity
							) * x 
						- 2 
							* (
								variables::limits::maximal::wheel_velocity
								) 
							* x
							)
				- 2 
					* (
						variables::limits::minimal::wheel_velocity
						) 
					* std::pow(x, 2)
				+ 2 
					* (
						variables::limits::maximal::wheel_velocity
						)
					* std::pow(x, 2)
				)
			/ (
				std::pow(
					std::pow(
						acceleration_const 
						+ std::pow(x, 2)
						, offset)
					, 2)
				* (
					acceleration_const 
					+ std::pow(x, 2)
					)
				+ std::pow(
					acceleration_const 
					+ std::pow(x, 2)
					, offset)
						* std::pow(
							acceleration_const 
							+ std::pow(x, 2)
							, x)
						* (2 
							* (acceleration_const) 
							+ 2 * std::pow(x, 2)
							) 
				+ std::pow(
					std::pow(
						(acceleration_const + std::pow(x, 2))
						, x)
					, 2)
				* (
					acceleration_const 
					+ std::pow(x, 2)
					)
				);
	}
