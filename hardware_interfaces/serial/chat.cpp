/*
 * chat.cpp
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

#include "chat.hpp"


chat::chat(){
	
	}



chat::chat(serial &s){
	this -> main_serial = &s;
	}


void chat::init(serial &s){
	this -> main_serial = &s;
	//~ this -> main_serial -> open();
	}



bool chat::run(steady now){
	if(main_serial -> in_waiting() != 0){
		std::vector<uint8_t> appended(main_serial -> in_waiting());
		main_serial -> read(appended);
		for(uint8_t a: appended){
			input_buffer.push_back(a);
			if(a == msg_std::end)
				if(input_buffer.size() >= msg_std::length)
					if(input_buffer.at(input_buffer.size() - (msg_std::length)) == msg_std::start){
						std::array<uint8_t, msg_std::length> msg;
						unsigned_b offset = input_buffer.size() - (msg_std::length);
						for(unsigned_b i = 0; i < msg_std::length; i++)
							msg.at(i) = input_buffer.at(i + offset);
						input_queue.emplace_back(msg);
						// clearing the buffer from that message and from what came before
						input_buffer.erase(input_buffer.begin(), input_buffer.begin() + offset);
						std::cout << "EMPLACED STH" << std::endl;
						}
			}
		}

	for(unsigned_b i = 0; i < input_queue.size(); i++)
		for(auto &q: output_queue)
			if(q.answers_query(input_queue.at(i))){
				q.answer(input_queue.at(i));
				input_queue.erase(input_queue.begin() + i--);
				}
	return true;
	}

