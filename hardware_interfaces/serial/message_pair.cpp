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
#include <cinttypes>

message_pair::message_pair(message m, unsigned_b timeout){
	this -> first = m;
	this -> response_timeout = timeout;
	}
	


message_pair::message_pair(fire_sensor* p, message m, unsigned_b timeout){
	this -> first = m;
	this -> response_timeout = timeout;
	periphery.emplace<fire_sensor*>(p);
	//~ printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



message_pair::message_pair(ground_sensor* p, message m, unsigned_b timeout){
	this -> first = m;
	this -> response_timeout = timeout;
	periphery.emplace<ground_sensor*>(p);
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	printf("response: %i\n", timeout);
	}



message_pair::message_pair(lidar* p, message m, unsigned_b timeout){
	this -> first = m;
	this -> response_timeout = timeout;
	periphery.emplace<lidar*>(p);
	}



message_pair::message_pair(motors* mr, message m, unsigned_b timeout){
	this -> first = m;
	this -> response_timeout = timeout;
	periphery.emplace<motors*>(mr);
	}



message_pair::message_pair(turbine* t, message m, unsigned_b timeout){
	this -> first = m;
	this -> response_timeout = timeout;
	periphery.emplace<turbine*>(t);
	}



message_pair::message_pair(thermocam* th, message m, unsigned_b timeout){
	this -> first = m;
	this -> response_timeout = timeout;
	periphery.emplace<thermocam*>(th);
	}



void message_pair::question(){
	//~ &message_pair::first, this,
	std::visit([this](auto arg){arg -> encode(); this -> first = arg -> output;}, periphery);
	}



void message_pair::answer(message m){
	std::visit([m](auto arg){arg -> fill_input(m);}, periphery);
	std::visit([](auto arg){arg -> decode();}, periphery);
	std::visit([](auto arg){arg -> answer();}, periphery);
	// this cannot be that easy - template arguments
	//~ std::get<periphery.index()>(periphery) -> fill_input(m);
	//~ std::get<periphery.index())>(periphery) -> decode();
	//~ std::get<periphery.index())>(periphery) -> answer();
	}



void message_pair::answer(){
	std::visit([](auto arg){arg -> answer();}, periphery);
	//~ std::get<periphery.index())>(periphery) -> answer();
	}



bool message_pair::answers_query(message m){
	std::vector<uint8_t> kind;
	std::visit([&kind, m](auto arg){
		kind = (arg -> get_comp_kind(m._content.kind));}, periphery);
	if(this -> first._content.receiver == m._content.sender &&
		this -> first._content.message_number <= m._content.message_number){
		for(uint8_t kind: kind){
			if(m._content.kind == kind)
				return true;
				}
		}
	return false;
	}


