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
#include "message_standard.hpp"
#include "message.hpp"

#ifndef MESSAGE_CPP
#define MESSAGE_CPP

message::message(){
	
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

void message::encode(message::content &in, uint8_t *buffer[msg_std::length]){
	*buffer[0] 					= msg_std::start;
	*buffer[msg_std::head] 		= (in.receiver << 5) | (in.sender << 2) | (in.type << 1) | (in.kind >> 2);
	*buffer[msg_std::head + 1] 	= (in.kind << 6) | (in.message_number >> 16 & 31);
	*buffer[msg_std::head + 2] 	= in.message_number >> 8 & 255;
	*buffer[msg_std::head + 2] 	= in.message_number & 255;
	
	memcpy(buffer[msg_std::message_space], &in.message_space, msg_std::message_space_size);
	
	*buffer[msg_std::length - 1] = msg_std::end;
}

#endif
