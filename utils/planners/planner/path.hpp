/*
 * path.hpp
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


#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include <string>
#include <sstream>
#include "step.hpp"

class path: public std::vector<step> {
	public:
		unsigned is_complete: 		1;
		unsigned variable_start: 	1; // allows anydirectional start, default true
		unsigned variable_end: 		1; // allows anydirectional end
		unsigned definite_start: 	1; // allows start on any coordinates
		unsigned definite_end: 		1; // allows end on any coordinates
		
		decimal_n angle_start = 0;
		decimal_n angle_end = 0;
		
		using std::vector<step>::push_back;
		using std::vector<step>::pop_back;
		using std::vector<step>::emplace_back;
		using std::vector<step>::back;
		using std::vector<step>::front;
		using std::vector<step>::begin;
		using std::vector<step>::end;
		using std::vector<step>::cbegin;
		using std::vector<step>::cend;
		using std::vector<step>::assign;
		using std::vector<step>::get_allocator;
		using std::vector<step>::at;
		using std::vector<step>::operator[];
		using std::vector<step>::empty;
		using std::vector<step>::size;
		using std::vector<step>::reserve;
		using std::vector<step>::capacity;
		using std::vector<step>::shrink_to_fit;
		using std::vector<step>::clear;
		using std::vector<step>::data;
		
		path(std::vector<step> copy, bool start = true, bool end = true);
		path(const path& copy);
		path(step copy, bool start = true, bool end = false, bool complete = false);
		
		std::string print();
		
		void set_variable_start(bool state);
		void set_variable_end(bool state);
		void set_definite_start(bool state);
		void set_definite_end(bool state);
		void set_completness(bool state);
		
		bool get_variable_start();
		bool get_variable_end();
		bool get_definite_start();
		bool get_definite_end();
		bool get_completness();
		
		
	private:
		/* add your private declarations */
};

#endif /* PATH_HPP */ 
