/*
 * message_pair.cpp
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


#include "message_pair.hpp"


message_pair::message_pair() : std::pair<message, message>(){
	
	}
	


message_pair::message_pair(std::shared_ptr<serial_peripheral> p) : std::pair<message, message>(){
	periphery = p;
	}



void message_pair::answer(message m){
	periphery -> fill_input(m);
	periphery -> decode();
	periphery -> answer();
	}



void message_pair::answer(){
	periphery -> answer();
	}



bool message_pair::answers_query(message m){
	if(this -> first._content.receiver == m._content.sender &&
		this -> first._content.message_number <= m._content.message_number)
		for(uint8_t kind: periphery -> get_comp_kind(m._content.kind))
			if(m._content.kind == kind)
				return true;
	return false;
	}


