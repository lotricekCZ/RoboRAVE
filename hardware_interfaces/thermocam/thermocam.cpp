/*
 * thermocam.cpp
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

#include <memory>
#include <array>
#include <iostream>

#include "../serial/chat.hpp"
#include "../../utils/data_containers/angles/node/node.hpp"
#include "thermocam.hpp"

/*
 * 
 * name: thermocam
 * 
 */

thermocam::thermocam() : serial_peripheral(){
	this -> comp_kinds = table;
	}



thermocam::thermocam(chat *c) : serial_peripheral(c){
	//~ this -> sensor = std::vector<node> ();

	printf("_conn pointer = %p\n", _conn);
	this -> comp_kinds = table;
	}



thermocam::thermocam(chat &c) : serial_peripheral(c){
	this -> _conn = &c;
	this -> comp_kinds = table;
	}


thermocam::~thermocam(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

/*
bool thermocam::update(){
	/// TODO: update
	return false;
	}

std::vector<node> thermocam::get_data(bool update = false){
	std::vector<node> ret;
	/// TODO: get data
	return ret;
	}
*/


void thermocam::question(){
	//~ printf("main = %p\n", _conn);
	if(queue >= variables::chat::max_queue_sensor) return;
	this -> _conn -> question(output, this);
	queue++;
	return;
	}



void thermocam::answer(){
	if(queue != 0) queue--;
	has_data = 1;
	return;
	}



void thermocam::decode(){
	this -> presets.current_index = ((0b10 & input._content.message_space[0]) >> 7) | input._content.message_space[1] >> 7;
	for(uint8_t i = 0; i < 16; i++){
		this -> sensor.at(((i/4) * 2 + (presets.current_index >> 1) & 1))
					.at((i % 4) + (presets.current_index) & 1) = ((input._content.message_space[i] & 127) - 47);
		}
	return;
	}



void thermocam::encode(){
	this -> output._content.receiver = variables::addressbook::gndduino;
	this -> output._content.sender = variables::addressbook::master;
	this -> output._content.type = chat::COMMAND;
	this -> output._content.kind = thermocam::SND_DAT;
	
	this -> output._content.message_space[0] = this -> presets.first_index << 6 | this -> presets.last_index << 4;
	return;
	}



void thermocam::run(){
	//~ message
	return;
	}



void thermocam::update(){
	//~ message
	std::cout << "This is thermocam" << std::endl;
	return;
	}


/*
thermocam& thermocam::operator=(const thermocam& rhs) {
	// thermocam stuff here
	
	// serial_peripheral stuff
	//~ serial_peripheral::operator=(rhs.);
	
	return *this;
	}
*/	
	
	
