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
#include <variant>
#include <vector>
#include <memory>
#include "../../defines/typedefines.h"
#include "serial_peripheral.hpp"
#include "../lidar/lidar.hpp"
#include "../fire_sensors/fire_sensor.hpp"
#include "../ground_sensors/ground_sensor.hpp"
#include "../motors/motors.hpp"
#include "../turbine/turbine.hpp"
#include "message.hpp"
#include <cinttypes>

class message_pair{
	public:
		message first;
		message second;
		std::variant<fire_sensor*, 
					lidar*,
					turbine*, 
					ground_sensor*, 
					motors*
					/*, thermocam* */> periphery;
		steady appear_first;
		steady try_last;
		uint8_t tries = 0;
		unsigned_b response_timeout = variables::chat::response_timeout::normal;
		bool awaits_second; // some messages (e. g. Motorduino) needn't a confirmator/response message
		void answer(message m);
		void answer();
		bool answers_query(message m);
		void question();
		
		message_pair(message m = message(), unsigned_b timeout = variables::chat::response_timeout::normal);
		
		message_pair(ground_sensor* p, message m = message(), unsigned_b timeout = variables::chat::response_timeout::normal);
		message_pair(fire_sensor* p, message m = message(), unsigned_b timeout = variables::chat::response_timeout::normal);
		message_pair(lidar* p, message m = message(), unsigned_b timeout = variables::chat::response_timeout::normal);
		message_pair(motors* mr, message m = message(), unsigned_b timeout = variables::chat::response_timeout::time_critical);
		message_pair(turbine* t, message m = message(), unsigned_b timeout = variables::chat::response_timeout::normal);
		/*
		message_pair& operator=(message_pair other){
			std::cout << "copy assignment of A\n";
			std::swap(first, other.first);
			std::swap(second, other.second);
			std::swap(periphery, other.periphery);
			std::swap(appear_first, other.appear_first);
			std::swap(try_last, other.try_last);
			std::swap(tries, other.tries);
			std::swap(awaits_second, other.awaits_second);
			return *this;
			}*/
		//~ message_pair(ground_sensors* p, message m = message());
		//~ message_pair(thermocam* p, message m = message());
		//~ message_pair(motors* p, message m = message());
			
	private:
		/* add your private declarations */
};

#endif /* MESSAGE_PAIR_HPP */ 
