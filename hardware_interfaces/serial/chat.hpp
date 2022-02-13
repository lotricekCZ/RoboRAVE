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
#include <memory>
#include <array>
#include <deque>
#include "../../defines/typedefines.h"
#include "serial.hpp"
#include "serial_peripheral.hpp"
#include "message.hpp"
#include "message_pair.hpp"
#include "addressbook.hpp"

class chat {
	public:
		chat();
		chat(serial &s);
		serial *main_serial;
		std::deque<message> input_queue; // messages that aren't still assigned to query
		std::deque<message_pair> output_queue;
		bool run(steady now = time_now); // iterates through message queue, searching for responses.
		std::deque<uint8_t> input_buffer;
		void init(serial &s);
	private:
		/* add your private declarations */
};

#endif /* CHAT_HPP */ 
