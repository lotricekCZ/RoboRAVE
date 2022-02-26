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



chat::chat(serial &s, rpi_gpio &r){
	output_queue = std::vector<message_pair>();
	this -> main_serial = &s;
	this -> main_gpio = &r;
	}



void chat::init(serial &s, rpi_gpio &r){
	//~ output_queue = std::vector<message_pair>();
	this -> main_serial = &s;
	this -> main_gpio = &r;
	//~ this -> main_serial -> open();
	}



void chat::question(message m, lidar* l){
	output_queue.emplace_back((lidar*)l, m);
	l -> update();
	this -> output_queue.back().awaits_second = (m._content.receiver == variables::addressbook::motorduino);
	this -> output_queue.back().question();
	}



void chat::question(message m, thermocam* th){
	output_queue.emplace_back((thermocam*) th, m);
	th -> update();
	this -> output_queue.back().awaits_second = (m._content.receiver == variables::addressbook::motorduino);
	this -> output_queue.back().question();
	}



void chat::question(message m, motors* mr){
	output_queue.emplace_back((motors*)mr, m);
	mr -> update();
	this -> output_queue.back().awaits_second = (m._content.receiver == variables::addressbook::motorduino);
	this -> output_queue.back().question();
	}



void chat::question(message m, turbine* t){
	output_queue.emplace_back((turbine*)t, m);
	t -> update();
	this -> output_queue.back().awaits_second = (m._content.receiver == variables::addressbook::motorduino);
	this -> output_queue.back().question();
	}



void chat::question(message m, fire_sensor* f){
	//~ std::shared_ptr<message_pair> a(new );
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	output_queue.emplace_back((fire_sensor*)f, m);
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	f -> update();
	this -> output_queue.back().awaits_second = (m._content.receiver == variables::addressbook::motorduino);
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	this -> output_queue.back().question();
	}



void chat::question(message m, ground_sensor* f){
	//~ std::shared_ptr<message_pair> a(new );
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	output_queue.emplace_back((ground_sensor*)f, m);
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	f -> update();
	this -> output_queue.back().awaits_second = (m._content.receiver == variables::addressbook::motorduino);
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << std::endl;
	this -> output_queue.back().question();
	}



/*
printf("\tsender:\t\t%u\n\treceiver:\t%u\n\ttype:\t\t%u\n\tkind:\t\t%u\n\tnumber:\t\t%u\n\tbyteload:\t\t", 
	m.first._content.sender,
	m.first._content.receiver,
	m.first._content.type,
	m.first._content.kind,
	m.first._content.message_number
	);
for(auto o: m.first._content.message_space) printf("%x  ", o);
std::cout << std::endl;
*/


void chat::send(message_pair *m, steady now){
	//~ std::ofstream o("Ahoy.bin", std::ios::out | std::ios::app | std::ios::binary);
	//~ std::cout << "BEFORE: " << std::chrono::duration_cast<std::chrono::seconds>(m.try_last.time_since_epoch()).count() << std::endl;
	bool pin_state = main_gpio -> get_state();
	if(m -> first._content.message_number == 0) m -> first._content.message_number = message_num++;
	m -> try_last = now;
	m -> tries++;
	std::cout << "AFTER: " << std::chrono::duration_cast<std::chrono::seconds>(m -> try_last.time_since_epoch()).count() << std::endl;
	std::array<uint8_t, msg_std::length> bfr;
	m -> first.encode(m -> first._content, bfr);
	std::vector<uint8_t> sended(&bfr[0], &bfr[msg_std::length]);
	main_serial -> write(sended);
	printf("DISABLING SERIAL, IN next 4.5s nothing\n");
	}



bool chat::handle_port(steady now){
	//~ bool pin_state = main_gpio -> get_state();
	if(port_state == FREE && now >= message_send_time){
		port_state = OPENING; // after it will be closed
		message_send_time = now + std::chrono::milliseconds(variables::chat::port_delay);
		printf("DISABLING SERIAL\n");
		return 0;
		}
	
	if(port_state == OPENING && now >= message_send_time){
		port_state = SEND; // after it will be closed
		message_send_time = now + std::chrono::milliseconds(variables::chat::port_delay);
		printf("DISABLING SERIAL\n");
		return 0;
		}
	
	if(port_state == SEND && now >= message_send_time){
		port_state = SEND; // after it will be closed
		message_send_time = now + std::chrono::milliseconds(variables::chat::port_delay);
		printf("DISABLING SERIAL\n");
		return 1;
		}
		
	if(port_state == CLOSING && now >= message_send_time){
		port_state = FREE; // after it will be closed
		main_gpio -> disable_serial();
		printf("SERIAL DISABLED\n");
		return 0;
		}
	return 0;
	}



bool chat::stage(steady now){
	switch(port_state){
		case rs485_state::FREE: {
			printf("OPENING\n");
			port_state = rs485_state::OPENING;
			main_gpio -> enable_serial();
			message_send_time = time_now;
			return 0;
			}

		case rs485_state::OPENING: {
			if(std::chrono::duration<decimal_n>(now - message_send_time) 
				>= std::chrono::microseconds(variables::chat::port_delay)){
				port_state = rs485_state::SEND;
				printf("SEND\n");
				} else {return 0;}
			[[fallthrough]];
			}

		case rs485_state::SEND: {
			send(held, now);
			message_send_time = time_now;
			port_state = rs485_state::CLOSING;
			printf("CLOSING\n");
			return 1;
			}

		case rs485_state::CLOSING: {
			if(std::chrono::duration<decimal_n>(now - message_send_time) 
				>= std::chrono::microseconds(variables::chat::port_delay)){
				main_gpio -> disable_serial();
				port_state = rs485_state::FREE;
				printf("CLOSED\n");
				}
			return 0;
			}

		}
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
						printf("\n----RECEIVED----\n\tsender:\t\t%u\n\treceiver:\t%u\n\ttype:\t\t%u\n\tkind:\t\t%u\n\tnumber:\t\t%u\n\tbyteload:\t\t", 
							input_queue.back()._content.sender,
							input_queue.back()._content.receiver,
							input_queue.back()._content.type,
							input_queue.back()._content.kind,
							input_queue.back()._content.message_number
							);
						// clearing the buffer from that message and from what came before
						input_buffer.erase(input_buffer.begin(), input_buffer.begin() + offset);
						std::cout << "EMPLACED STH" << std::endl;
						}
			}
		}
		
	for(unsigned_b i = 0; i < input_queue.size(); i++){
		for(unsigned_b o = 0; o < output_queue.size(); o++){
			if(output_queue.at(o).answers_query(input_queue.at(i))){
				output_queue.at(o).answer(input_queue.at(i));
				input_queue.erase(input_queue.begin() + i--);
				output_queue.erase(output_queue.begin() + o--); // NEEDS TO BE ANSWERED !!!
				if(input_queue.size() == 0) break;
				}
			}
		}
		
	switch(port_state){
		case rs485_state::FREE: {
			for(unsigned_b i = 0; i < output_queue.size(); i++){
				//~ printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
				if(std::chrono::duration<decimal_n>(now - output_queue.at(i).try_last) 
					>= std::chrono::milliseconds(output_queue.at(i).response_timeout)){
					//~ printf("RESPONSE IS HERE!\n");
					if(output_queue.at(i).tries >= variables::chat::attempt_count) {
						output_queue.at(i).answer();
						output_queue.erase(output_queue.begin() + i--);
						continue;
						}
					port_state = rs485_state::OPENING;
					held = &output_queue.at(i);
					break;
					}
				}
			if(port_state == rs485_state::FREE) break;
			port_state = rs485_state::FREE;
			}
		default: {
			stage(now);
			}
		}
	return true;
	}

