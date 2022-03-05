/*
 * path_wrapper.hpp
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


#ifndef PATH_WRAPPER_HPP
#define PATH_WRAPPER_HPP

#include "../planners/planner/path.hpp"
#include "../../elements/vector/vector.hpp"
#include "../../hardware_interfaces/serial/serial_peripheral.hpp"
#include "../../hardware_interfaces/motors/motors.hpp"

class path_wrapper: public path {
	public:
		//~ path_wrapper();
		path_wrapper(std::vector<step> copy, bool start = true, bool end = true);
		path_wrapper(const path& copy);
		path_wrapper(step copy, bool start = true, bool end = false, bool complete = false);
		//~ decimal_n now_angle = 0;
		
		using path::push_back;
		using path::pop_back;
		using path::emplace_back;
		using path::back;
		using path::front;
		using path::begin;
		using path::end;
		using path::cbegin;
		using path::cend;
		using path::rbegin;
		using path::rend;
		using path::assign;
		using path::get_allocator;
		using path::at;
		using path::operator[];
		using path::empty;
		using path::size;
		using path::reserve;
		using path::capacity;
		using path::shrink_to_fit;
		using path::clear;
		using path::data;
		using path::insert;
		using path::iterator;
		using path::erase;
		
		
		using path::print;
		//~ void insert(std::vector<step>::iterator, path inserted);
		using path::reorder;
		using path::assemble;
		using path::delete_zero_length;
		
		using path::set_variable_start;
		using path::set_variable_end;
		using path::set_definite_start;
		using path::set_definite_end;
		using path::set_completness;
		
		using path::get_variable_start;
		using path::get_variable_end;
		using path::get_definite_start;
		using path::get_definite_end;
		using path::get_completness;
		
		using path::get_intersections_all;
		using path::get_intersections;
		
		using path::get_intersections_all;
		using path::get_intersections;
		
		steady last = time_now;
		std::chrono::duration<decimal_n> duration;
		unsigned_b head = 0; // to know which step to translate
		decimal_n speed_level = 0;
		decimal_n remainder = 0; // what's left after division
		speeds now_speeds = speeds(0, 0);
		
		decimal_n get_velocity(decimal_n x);
		decimal_n get_closest(decimal_n x);
		decimal_n get_derivative(decimal_n x);
		bool its_time(steady now = time_now);
		bool has_next();
		std::pair<uint8_t, std::array<motors::motor, 2>> translate();
	private:
		/* add your private declarations */
};

#endif /* PATH_WRAPPER_HPP */ 
