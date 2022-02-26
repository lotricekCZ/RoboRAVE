/*
 * fire_sensor.cpp
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
#include <vector>
#include <iostream>

#include "../serial/chat.hpp"
#include "../../utils/data_containers/angles/node/node.hpp"
#include "fire_sensor.hpp"

/*
 * 
 * name: fire_sensor
 * @param sensors - number of sensors included
 * @param spread - spread of each sensor 
 * @param range - general range of sensors
 * 
 */

fire_sensor::fire_sensor(uint8_t sensors, decimal_n spread, decimal_n range) : serial_peripheral(){
	this -> sensors = std::vector<node> (sensors);
	this -> range = range;
	this -> spread = spread;
	this -> comp_kinds = table;
	}



fire_sensor::fire_sensor(chat *c, uint8_t sensors, decimal_n spread, decimal_n range) : serial_peripheral(c){
	this -> sensors = std::vector<node> (sensors);
	this -> _conn = c;
	printf("_conn pointer = %p\n", _conn);
	this -> range = range;
	this -> spread = spread;
	this -> comp_kinds = table;
	}



fire_sensor::fire_sensor(chat &c, uint8_t sensors, decimal_n spread, decimal_n range) : serial_peripheral(c){
	this -> _conn = &c;
	printf("_conn = %p\n", _conn);
	this -> sensors = std::vector<node> (sensors);
	this -> range = range;
	this -> spread = spread;
	this -> comp_kinds = table;
	}


fire_sensor::~fire_sensor(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

/*
bool fire_sensor::update(){
	/// TODO: update
	return false;
	}

std::vector<node> fire_sensor::get_data(bool update = false){
	std::vector<node> ret;
	/// TODO: get data
	return ret;
	}
*/


void fire_sensor::question(){
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	printf("main = %p\n", _conn);
	if(queue >= variables::chat::max_queue_sensor) return;
	this -> _conn -> question(output, this);
	queue++;
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	return;
	}



void fire_sensor::answer(){
	if(queue != 0) queue--;
	return;
	}



void fire_sensor::decode(){
	for(uint8_t i = 0; i < 8; i++){
		this -> sensors.at(i).intensity = (input._content.message_space[i] << 2) | 
				((input._content.message_space[8 + i/4] >> (2 * (3 - i))) & 0b11);
		}
	this -> presets.reference = ((0b11 & input._content.message_space[10]) << 8) | input._content.message_space[11];
	return;
	}



void fire_sensor::encode(){
	this -> output._content.receiver = variables::addressbook::irduino;
	this -> output._content.sender = variables::addressbook::master;
	this -> output._content.type = chat::COMMAND;
	this -> output._content.kind = fire_sensor::SND_DAT;
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	this -> output._content.message_space[0] = this -> presets.period >> 8 		& 255;
	this -> output._content.message_space[1] = this -> presets.period			& 255;
	this -> output._content.message_space[2] = this -> presets.oversampling		& 31;
	this -> output._content.message_space[3] = this -> presets.expo_time >> 8	& 255;
	this -> output._content.message_space[4] = this -> presets.expo_time		& 255;
	return;
	}



void fire_sensor::run(){
	//~ message
	return;
	}



void fire_sensor::update(){
	//~ message
	std::cout << "This is fire sensor" << std::endl;
	return;
	}


/*
fire_sensor& fire_sensor::operator=(const fire_sensor& rhs) {
	// fire_sensor stuff here
	
	// serial_peripheral stuff
	//~ serial_peripheral::operator=(rhs.);
	
	return *this;
	}
*/	
	
	
