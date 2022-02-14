/*
 * serial_peripheral.cpp
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


#include "chat.hpp"
#include "serial_peripheral.hpp"

class chat;


serial_peripheral::serial_peripheral(){
	}
	


serial_peripheral::serial_peripheral(chat *c){
	
	}



serial_peripheral::serial_peripheral(chat &c){
	
	}


	
serial_peripheral::~serial_peripheral(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	}



void serial_peripheral::fill_input(message in){
	input = in;
	}



std::vector<uint8_t> serial_peripheral::get_comp_kind(uint8_t kind){
	for(auto [key, kinds]: comp_kinds) if(key == kind) return kinds;
	return std::vector<uint8_t>();
	}



void serial_peripheral::get_comp_kind(uint8_t kind, std::vector<uint8_t> &v){
	for(auto [key, kinds]: comp_kinds) if(key == kind) {v = kinds; return;}
	v = std::vector<uint8_t>();
	}
