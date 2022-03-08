/*
 * motors.cpp
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
#include "motors.hpp"

/*
 * 
 * name: motors
 * @param sensors - number of sensors included
 * @param spread - spread of each sensor 
 * @param range - general range of sensors
 * 
 */

motors::motors() : serial_peripheral(){
	}



motors::motors(chat *c) : serial_peripheral(c){
	this -> _conn = c;
	}



motors::motors(chat &c) : serial_peripheral(c){
	this -> _conn = &c;
	}


motors::~motors(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

/*
bool motors::update(){
	/// TODO: update
	return false;
	}

std::vector<node> motors::get_data(bool update = false){
	std::vector<node> ret;
	/// TODO: get data
	return ret;
	}
*/


void motors::question(){
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	//~ printf("main = %p\n", _conn);
	if(queue >= variables::chat::max_queue_sensor) return;
	this -> _conn -> question(output, this);
	queue++;
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	return;
	}



void motors::answer(){
	if(queue != 0) queue--;
	has_data = 1;
	return;
	}



void motors::decode(){
	right_data.remaining_steps = input._content.message_space[0] << 8 | input._content.message_space[1];
	
	left_data.remaining_steps = input._content.message_space[2] << 8 | input._content.message_space[3];
	
	right_data.high_interval = input._content.message_space[4] << 6 | input._content.message_space[5] >> 2;
	left_data.high_interval = input._content.message_space[6] << 6 | input._content.message_space[7] >> 2;
	right_data.direction = (motors::direction) (input._content.message_space[5] & 0b11);
	left_data.direction = (motors::direction) (input._content.message_space[7] & 0b11);
	
	right_data.traveled_steps = (input._content.message_space[8] << 24)
								| (input._content.message_space[9] << 16)
								| (input._content.message_space[10] << 8)
								| (input._content.message_space[11]);
	left_data.traveled_steps = (input._content.message_space[12] << 24)
								| (input._content.message_space[13] << 16)
								| (input._content.message_space[14] << 8)
								| (input._content.message_space[15]);
	return;
	}



void motors::encode(){
	this -> output._content.receiver = variables::addressbook::motorduino;
	this -> output._content.sender = variables::addressbook::master;
	this -> output._content.type = chat::COMMAND;
	this -> output._content.kind = motors::SET_MOT;
	
	this -> output._content.message_space[0] = left.scheduled_steps >> 8;
	this -> output._content.message_space[1] = left.scheduled_steps;
	
	this -> output._content.message_space[2] = right.scheduled_steps >> 8;
	this -> output._content.message_space[3] = right.scheduled_steps;

	this -> output._content.message_space[4] = left.high_interval >> 6;
	this -> output._content.message_space[5] = left.high_interval << 2 | left.direction;
	this -> output._content.message_space[6] = right.high_interval >> 6;
	this -> output._content.message_space[7] = right.high_interval << 2 | right.direction;

	this -> output._content.message_space[8] = left.low_interval >> 6;
	this -> output._content.message_space[9] = left.low_interval << 2 | left.chain;
	this -> output._content.message_space[10] = right.low_interval >> 6;
	this -> output._content.message_space[11] = right.low_interval << 2 | right.chain;
										
	this -> output._content.message_space[12] = erase_flags | (right.rewrite << 1) | left.rewrite;
	}



void motors::run(){
	//~ message
	return;
	}



void motors::update(){
	//~ message
	std::cout << "This is motor" << std::endl;
	return;
	}



bool motors::assign(std::array<motors::motor, 2> in, uint8_t status){
	this -> left = in.at(0);
	this -> right = in.at(1);
	this -> erase_flags = status;
	if(queue >= variables::chat::max_queue_sensor) return false;
	encode();
	question();
	//~ message
	std::cout << "This is motor" << std::endl;
	return true;
	}


/*
motors& motors::operator=(const motors& rhs) {
	// motors stuff here
	
	// serial_peripheral stuff
	//~ serial_peripheral::operator=(rhs.);
	
	return *this;
	}
*/	
	
	
