/*
 * message.cpp
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


#include <cinttypes>
#include <cstring>

#include "../../defines/typedefines.h"
#include "message.hpp"

#ifndef MESSAGE_CPP
#define MESSAGE_CPP

message::message(){
	this -> _content.message_number = 0;
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



message::message(message::content c){
	this -> _content.message_number = 0;
	this -> _content = c;
	}



message::message(std::array<uint8_t, msg_std::length> c){
	this -> _content.message_number = 0;
	decode(c, this -> _content);
	}



bool message::decode(uint8_t buffer[msg_std::length], message::content &in){
	
	// check if it has characters defined in message standard
	
	if(buffer[0] == msg_std::start && buffer[msg_std::length - 1] == msg_std::end){
		
		in.receiver			= (buffer[msg_std::head] & 0b111 << 5) >> 5;
		in.sender			= (buffer[msg_std::head] & 0b111 << 2) >> 2;
		in.type				= (buffer[msg_std::head] & 0b10) >> 1;
		in.kind				= (((buffer[msg_std::head]) << 2) | (buffer[msg_std::head + 1]  >> 6)) & 0b111;
		in.message_number 	= (((buffer[msg_std::head + 1] & 0b111111) << 16) | (buffer[msg_std::head + 2] << 8) | buffer[msg_std::head + 3]);
		
		memcpy(&in.message_space, &buffer[msg_std::message_space], msg_std::message_space_size);
		return true;	// message is valid
		} else {
			return false;	// message is invalid
			}
	}



bool message::decode(std::array<uint8_t, msg_std::length> buffer, message::content &in){
	uint8_t bfr[msg_std::length];
	for(unsigned_b i = 0; i < msg_std::length; i++)
		bfr[i] = buffer.at(i);
	return decode(bfr, in);
	// check if it has characters defined in message standard
	
	}



void message::encode(message::content &in, std::array<uint8_t, msg_std::length> &buffer){
	buffer[0] 					= msg_std::start;
	buffer[msg_std::head] 		= (in.receiver << 5) | (in.sender << 2) | (in.type << 1) | (in.kind >> 2);
	buffer[msg_std::head + 1] 	= (in.kind << 6) | (in.message_number >> 16 & 31);
	buffer[msg_std::head + 2] 	= in.message_number >> 8 & 255;
	buffer[msg_std::head + 3] 	= in.message_number & 255;
	
	for(uint8_t i = 0; i < msg_std::message_space_size; i++)
		buffer[msg_std::message_space + i] = in.message_space[i];
	
	buffer[msg_std::length - 1] = msg_std::end;
	}

#endif
