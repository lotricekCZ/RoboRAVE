/*
 * lidar.cpp
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

#include "../serial/chat.hpp"
#include "lidar.hpp"


lidar::lidar(decimal_n rng) : serial_peripheral() {
	this -> receiver = variables::addressbook::stm;
	range = rng;
	comp_kinds = table;
	}



lidar::lidar(chat *c, decimal_n rng) : serial_peripheral(c) {
	this -> receiver = variables::addressbook::stm;
	range = rng;
	comp_kinds = table;
	}



lidar::lidar(chat &c, decimal_n rng) : serial_peripheral(c) {
	this -> receiver = variables::addressbook::stm;
	range = rng;
	comp_kinds = table;
	}



void lidar::question(){
	if(queue >= variables::chat::max_queue_sensor) return;
	this -> _conn -> question(output, this);
	queue++;
	return;
	}



void lidar::answer(){
	if(queue != 0) queue--;
	return;
	}



void lidar::decode(){
	steady now = time_now;
	uint8_t count = input._content.message_space[0] & 0b11;
	if(count == 0) std::cout << "No results, did you update?" << std::endl;
	for(uint8_t i = 0; i < count; i++){
		uint16_t distance = (input._content.message_space[i * 5 + 1] << 8) 
								| input._content.message_space[i * 5 + 2] >> 3;
		uint16_t angle = 	input._content.message_space[i * 5 + 2] << 6 
								| input._content.message_space[i * 5 + 3] >> 2;
		uint16_t age = 		input._content.message_space[i * 5 + 3] << 14 
								| input._content.message_space[i * 5 + 4] << 6
								| input._content.message_space[i * 5 + 5] >> 2;
		conv_vals.emplace_back((lidar::value_time){distance, angle, now - std::chrono::milliseconds(age)}); // this is strange, yet reasonable
		}
	convert = true;
	return;
	}



void lidar::encode(){
	output._content.message_space[0] = presets.first_index >> 1;
	output._content.message_space[1] = presets.first_index << 8 
										| presets.last_index >> 2;
	output._content.message_space[2] = presets.last_index << 6 
										| (presets.span << 2 & 15) 
										| (presets.tolerable_age >> 7);
	output._content.message_space[3] = presets.tolerable_age << 2;
	return;
	}



void lidar::run(){
	//~ message
	return;
	}



void lidar::update(){
	//~ message
	return;
	}


