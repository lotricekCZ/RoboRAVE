/*
 * turbine.cpp
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
#include "turbine.hpp"

/*
 * 
 * name: turbine
 * @param sensors - number of sensors included
 * @param spread - spread of each sensor 
 * @param range - general range of sensors
 * 
 */

turbine::turbine() : serial_peripheral(){
	}



turbine::turbine(chat *c) : serial_peripheral(c){
	this -> _conn = c;
	}



turbine::turbine(chat &c) : serial_peripheral(c){
	this -> _conn = &c;
	}



turbine::~turbine(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	}



void turbine::question(){
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	this -> _conn -> question(output, this);
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	return;
	}



void turbine::answer(){
	if(queue != 0) queue--;
	return;
	}



void turbine::decode(){
	// No sensor means there aren't any reasonable data
	return;
	}



void turbine::encode(){
	this -> output._content.receiver = variables::addressbook::motorduino;
	this -> output._content.sender = variables::addressbook::master;
	this -> output._content.type = chat::COMMAND;
	this -> output._content.kind = turbine::MOV_TRB;
	
	this -> output._content.message_space[0] = data.state_duration >> 6;
	this -> output._content.message_space[1] = data.state_duration << 2 
												| ((data.turbine_steps >> 10) & 0b11);
	this -> output._content.message_space[2] = data.state_duration >> 2;
	this -> output._content.message_space[3] = data.state_duration << 10 
												| (((uint8_t)data.stepper_dir & 0b11) << 4) 
												| (((uint8_t)data.motor_opt & 0b1) << 3)
												| (((uint8_t)data.option & 0b111));
	this -> output._content.message_space[4] = (data.hold << 7) 
												| data.turbine_tilt >> 5;
	this -> output._content.message_space[5] = (data.turbine_tilt << 3); 
	}



void turbine::run(){
	//~ message
	return;
	}



void turbine::update(){
	//~ message
	std::cout << "This is motor" << std::endl;
	return;
	}	
