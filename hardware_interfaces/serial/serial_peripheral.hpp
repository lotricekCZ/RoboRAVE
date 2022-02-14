/*
 * serial_peripheral.hpp
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


#ifndef SERIAL_PERIPHERAL_HPP
#define SERIAL_PERIPHERAL_HPP

#include <map>
#include <vector>
#include <iostream>

#include "../../defines/typedefines.h"
#include "../../defines/variables.hpp"
#include "message.hpp"

class chat;

//~ template<typename T>
class serial_peripheral{
	public:
		unsigned receiver:	3;
		
		serial_peripheral();
		serial_peripheral(chat *_c);
		serial_peripheral(chat &_c);
		~serial_peripheral();
		
		//~ chat * _conn;
		message output;
		message input;
		//~ T * peripheral; // peripheral that actually stands behind
		std::map<uint8_t, std::vector<uint8_t>> comp_kinds; // complementary kinds
		
		std::vector<uint8_t> get_comp_kind(uint8_t kind);
		void get_comp_kind(uint8_t kind, std::vector<uint8_t> &v);
		void fill_input(message in);
		virtual void run(){}
		virtual void question(){}
		virtual void answer(){}
		virtual void decode(){}
		virtual void encode(){}
		virtual void update(){std::cout << "This is reason for hate crime" << std::endl;}
	private:
		/* add your private declarations */
	};

#endif /* SERIAL_PERIPHERAL_HPP */ 
