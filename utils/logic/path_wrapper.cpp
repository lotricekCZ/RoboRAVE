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
			speed_level = 0; // dynamically change
			remainder = 0;
			decimal_n max_speed = std::max(variables::limits::minimal::wheel_velocity, 
										std::max(now_speeds.left, now_speeds.right)) * 0.8;
				// this max speed will be used for the faster (longer) lane
				/// Notice the 20% drop - possibly change
			decimal_n radius = this -> at(head).start.get_distance(this -> at(head).get_center());
			decimal_n lengths[2] = {((radius - (10.0f * (decimal_n)dist_wheel / 2.0f)) * this -> at(head).angle()), 
									((radius + (10.0f * (decimal_n)dist_wheel / 2.0f)) * this -> at(head).angle())};
			/// TODO: THE 10x multiplier may be removed
			decimal_n ratio = (std::min(lengths[0], lengths[1]) / std::max(lengths[0], lengths[1]));
			decimal_n low_speed = max_speed * ratio;
			if(std::abs(low_speed) != 0 && std::abs(low_speed) < variables::limits::minimal::wheel_velocity){
				decimal_n anti_ratio = variables::limits::minimal::wheel_velocity / low_speed;
				low_speed *= std::abs(anti_ratio); // so that the sign doesn't change
				max_speed *= std::abs(anti_ratio);
				}
			decimal_n time = std::max(lengths[0], lengths[1]) / max_speed;
			//~ printf("time needed %f s\n", time);
			
			speeds s(((this -> at(head).direction_curve)? max_speed: low_speed),
					((!this -> at(head).direction_curve)? max_speed: low_speed));
			
			ret.at(0).high_interval = ret.at(0).low_interval = std::floor(now_speeds.to_hw_speed(s.left));
			ret.at(1).high_interval = ret.at(1).low_interval = std::floor(now_speeds.to_hw_speed(s.right));
			ret.at(0).scheduled_steps = std::floor((double)(1e6 * (double)time) / ret.at(0).high_interval);
			ret.at(1).scheduled_steps = std::floor((double)(1e6 * (double)time) / ret.at(1).high_interval);
			printf("right:\n\tsteps: %i\n\ttime:%i\nright:\n\tsteps: %i\n\ttime:%i\n", 
				ret.at(0).scheduled_steps,
				ret.at(0).high_interval,
				ret.at(1).scheduled_steps,
				ret.at(1).high_interval
				);
			now_speeds = s;
			break;
			}
			
		case step::line_e: {
			
			decimal_n min_speed = std::max(variables::limits::minimal::wheel_velocity, std::min(now_speeds.left, now_speeds.right)); 
			// Only place where going back is used when retracting (hopefully)
			//~ printf("sp now: %f\n", now_speeds.left);
			//~ printf("sr now: %f\n", now_speeds.right);
			decimal_n length = this -> at(head).length();
			decimal_n time = length / min_speed;
			
			if(time >= variables::step::acceleration_time && speed_level / 3.0f < 0.75f){
				coordinates inter = col_v(this -> at(head).start, 
							min_speed * variables::step::acceleration_time, 
							(this -> at(head).start.get_gamma(this -> at(head).end)), 1).get_point();
				this -> insert(this -> begin() + (head), step(this -> at(head).start, inter));
				this -> at(head + 1) = step(inter, this -> at(head + 1).end);
				status = 0b11111;
				}
			
			decimal_n steps = this -> at(head).length() / variables::wheel_step_length_const;
			speed_level += 0.1;
			speed_level = (speed_level > 3)? 3: (speed_level < 0)? 0: speed_level;
			
			decimal_n speed = get_velocity(speed_level);
			now_speeds.left = now_speeds.right = speed;
			remainder += (steps - std::floor(steps));
			ret.at(0).scheduled_steps = ret.at(1).scheduled_steps = std::floor(steps) + std::floor(remainder);
			ret.at(0).high_interval = ret.at(0).low_interval = 
				ret.at(1).high_interval = ret.at(1).low_interval = std::floor(now_speeds.to_hw_speed(speed));
			remainder -= std::floor(remainder); // this is to assure that not so many steps are lost
			break;
			}
		}
	last = time_now;
	duration = std::chrono::microseconds(((unsigned_b)ret.at(0).scheduled_steps * (unsigned_b)ret.at(0).high_interval));
	this -> at(head).time_start = std::chrono::duration<decimal_n>(first - last).count();
	this -> at(head).time = duration.count();
	this -> at(head).v = now_speeds;
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



bool path_wrapper::its_time(steady now){ 
	if(std::chrono::duration<decimal_n>(now - last) >= duration)
		printf("\nTIME: %f\tDUR: %f\n", std::chrono::duration<decimal_n>(now - last).count(), duration.count());
	return std::chrono::duration<decimal_n>(now - last) >= duration;
	}



bool path_wrapper::has_next(){ 
	return head < this -> size();
	}



node path_wrapper::backtrack(steady point){ 
	decimal_n time = std::chrono::duration<decimal_n>(point - first).count();
	step affector; // the one in which an effect occured
	if(time <= 0 && this -> size() > 0) return node(this -> front().angle_start, this -> front().start);
	for(unsigned_b head_n = head; head_n <= head; head_n--){
		if(time >= this -> at(head_n).time_start){
			affector = this -> at(head_n); // the one, whose start is older than current
			break;
			}
		}
	
	decimal_n delta = (time - affector.time_start);
	if(delta > affector.time) return node(affector.angle_end, affector.end);
	
	switch(affector._type){
		case step::line_e: {
			return node(affector.angle_start, col_v(affector.start, 
						affector.v.left * (delta), affector.angle_start).get_point());
			}
			
		case step::circle_e: {
			decimal_n angle_start_angle = affector.get_center().get_gamma(affector.start);
			decimal_n difference_angle = angle_start_angle + delta * affector.omega * (1 + ((affector.direction_curve)? -2: 0));
			col_v help = col_v(affector.get_center(), 
				affector.start.get_distance(affector.get_center()), 
				difference_angle);
			return node(help.angle() + ((affector.direction_curve)? -0.5f: 0.5f) * pi_const, help.get_point());
			break;
			}
		}
	}



decimal_n path_wrapper::get_closest(decimal_n x){
	decimal_n ret = 0;
	decimal_n diff = std::numeric_limits<decimal_n>::infinity();
	decimal_n y = get_derivative(x);
	for(uint8_t i = 0; i < 30; i++){
		decimal_n diff_c =  std::abs(get_velocity((decimal_n)i / 10.0f)/(y) - 1);
		//~ printf("\t%f\n", diff_c);
		if(diff_c < diff){
			diff = diff_c;
			
			ret = (decimal_n)i / 10.0f;
			}
		}
	//~ printf("RETURN %f", ret);
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
				); // BLACK METAL!!!
	}
