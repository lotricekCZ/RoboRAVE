/*
 * path.cpp
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


#include "path.hpp"


path::path(std::vector<step> copy, bool start, bool end) : std::vector<step>() {
	this -> assign(copy.begin(), copy.end());
	this -> angle_start = this -> begin() -> angle_start;
	this -> angle_end = this -> end() -> angle_end;
	this -> variable_start = start;
	this -> variable_end = end;
	}



path::path(step copy, bool start, bool end, bool complete) : std::vector<step>() {
	this -> push_back(copy);
	this -> angle_start = this -> begin() -> angle_start;
	this -> angle_end = this -> begin() -> angle_end;
	this -> is_complete = complete;
	this -> variable_start = start;
	this -> variable_end = end;
	}



path::path(const path& copy) : std::vector<step>() {
	*this = copy;
	}


/*
path::path(std::vector<step> copy) : std::vector<step>() {
	this -> assign(copy.begin(), copy.end());
	}
*/


void path::set_variable_start(bool state){
	this -> variable_start = state;
	}



void path::set_variable_end(bool state){
	this -> variable_end = state;
	}



void path::set_definite_start(bool state){
	this -> definite_start = state;
	}



void path::set_definite_end(bool state){
	this -> definite_end = state;
	}



void path::set_completness(bool state){
	this -> is_complete = state;
	}



bool path::get_variable_start(){
	return this -> variable_start;
	}



bool path::get_variable_end(){
	return this -> variable_end;
	}



bool path::get_definite_start(){
	return this -> definite_start;
	}



bool path::get_definite_end(){
	return this -> definite_end;
	}



bool path::get_completness(){
	return this -> is_complete;
	}

std::string path::print(){
	std::stringstream ret;
	for(auto o: *this)
		ret << o.print_geogebra() << std::endl;
		//~ ret << o.print_geogebra() << "\n";
	return ret.str();
	}


