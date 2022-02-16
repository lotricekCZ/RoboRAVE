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
#include <stdexcept>

chat::chat(){
	output_queue = std::vector<message_pair>();
	}



chat::chat(serial &s){
	output_queue = std::vector<message_pair>();
	this -> main_serial = &s;
	}



void chat::init(serial &s){
	//~ output_queue = std::vector<message_pair>();
	this -> main_serial = &s;
	//~ this -> main_serial -> open();
	}



void chat::question(message m, lidar* l){
	output_queue.emplace_back((lidar*)l, m);
	l -> update();
	this -> output_queue.back().awaits_second = (m._content.receiver == variables::addressbook::motorduino);
	}



void chat::question(message m, motors* mr){
	output_queue.emplace_back((motors*)mr, m);
	mr -> update();
	this -> output_queue.back().awaits_second = (m._content.receiver == variables::addressbook::motorduino);
	}



void chat::question(message m, fire_sensor* f){
	//~ std::shared_ptr<message_pair> a(new );
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	output_queue.emplace_back((fire_sensor*)f, m);
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	f -> update();
	this -> output_queue.back().awaits_second = (m._content.receiver == variables::addressbook::motorduino);
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	}



void chat::send(message_pair &m, steady now){
	std::cout << "BEFORE: " << std::chrono::duration_cast<std::chrono::seconds>(m.try_last.time_since_epoch()).count() << std::endl;
	m.try_last = now;
	m.tries++;
	std::cout << "AFTER: " << std::chrono::duration_cast<std::chrono::seconds>(m.try_last.time_since_epoch()).count() << std::endl;
	std::array<uint8_t, msg_std::length> bfr;
	m.first.encode(m.first._content, bfr);
	std::vector<uint8_t> sended(&bfr[0], &bfr[msg_std::length]);
	//~ printf("BEEN THERE: %i\n", __LINE__);
	main_serial -> write(sended);
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
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
	//~ printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	for(unsigned_b i = 0; i < input_queue.size(); i++)
		for(auto &q: output_queue)
			if(q.answers_query(input_queue.at(i))){
				q.answer(input_queue.at(i));
				input_queue.erase(input_queue.begin() + i--);
				} 
	
	//~ printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	printf("size: %i\n", output_queue.size());
	for(unsigned_b i = 0; i < output_queue.size(); i++){
		//~ printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		if(std::chrono::duration<decimal_n>(now - output_queue.at(i).try_last) >= std::chrono::milliseconds(output_queue.at(i).response_timeout)){
			//~ printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
			if(output_queue.at(i).tries >= variables::chat::attempt_count) {output_queue.erase(output_queue.begin() + i--); continue;}
			//~ printf("Length: %fs\n", std::chrono::duration<decimal_n>(q.try_last).count());
			printf("Length: %fs\n", std::chrono::duration<decimal_n>(now - output_queue.at(i).try_last).count());
			send(output_queue.at(i));
			std::cout << "OUTSIDE: " << std::chrono::duration_cast<std::chrono::seconds>(output_queue.at(i).try_last.time_since_epoch()).count() << std::endl;
			//~ printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
			}
		}
	return true;
	}

