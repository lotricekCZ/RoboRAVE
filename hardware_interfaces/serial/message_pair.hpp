/*
 * message_pair.hpp
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


#ifndef MESSAGE_PAIR_HPP
#define MESSAGE_PAIR_HPP

#include <utility>
#include "../../defines/typedefines.h"
#include "message.hpp"


class message_pair: public std::pair<message, std::vector<message>> {
	public:
		using std::pair<message, std::vector<message>>::first;
		using std::pair<message, std::vector<message>>::second;
		steady appear_first;
		steady try_last;
		uint8_t tries = 0;
		bool awaits_second; // some messages (e. g. Motorduino) needn't a confirmator/response message
		void answer(message m);
		message_pair();
			
	private:
		/* add your private declarations */
};

#endif /* MESSAGE_PAIR_HPP */ 
