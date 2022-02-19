/*
 * chat.hpp
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
 
#ifndef CHAT_HPP
#define CHAT_HPP

#include <cstring>
#include <variant>
#include <memory>
#include <array>
#include <deque>
#include "../../defines/typedefines.h"
#include "../gpio/rpi_gpio.hpp"
#include "serial.hpp"
#include "serial_peripheral.hpp"
#include "message.hpp"
#include "message_pair.hpp"
#include "addressbook.hpp"

class chat {
	public:
		enum message_t: uint8_t{COMMAND = 0, DATA = 1};
		chat();
		chat(serial &s);
		chat(serial &s, rpi_gpio &r);
		
		serial *main_serial;
		rpi_gpio *main_gpio;
		std::vector<message> input_queue; // messages that aren't still assigned to query
		std::vector<message_pair> output_queue;
		bool run(steady now = time_now); // iterates through message queue, searching for responses.
		std::deque<uint8_t> input_buffer;
		void init(serial &s, rpi_gpio &r);
		void send(message_pair &m, steady now = time_now);
		void question(message m, ground_sensor* f);
		void question(message m, fire_sensor* f);
		void question(message m, motors* mr);
		void question(message m, lidar* l);
		void question(message m, turbine* t);
		steady message_send_time = time_now;
		uint32_t message_num = 1;
		//~ void question(message m, ground_sensors* g);
		//~ void question(message m, thermocam* t);
	private:
		/* add your private declarations */
};

#endif /* CHAT_HPP */ 
