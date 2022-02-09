/*
 * logic.cpp
 * 
 * Copyright 2020 Jakub Ramašeuski <jakub@jakub-ThinkPad-X250>
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

#include <string>
#include <iostream>
#include <chrono>
#include <cstdio>

#include "../../elements/vector/vector.hpp"
#include "../../obsolete/obsolete.hpp"
#include "../../defines/variables.hpp"
#include "../../defines/typedefines.h"

#include "../data_containers/setters/setters.tpp"
#include "../data_containers/speeds/speeds.hpp"
#include "../data_containers/coordinates/coordinates.hpp"
#include "../data_containers/map/include.hpp"
#include "../data_containers/angles/angles/angles.hpp"

#include "../log_maintainer/log_maintain.hpp"

#include "../planners/avoidance_planner/avoider.hpp"
#include "../planners/planner/planner.hpp"

#include "../../hardware_interfaces/serial/serial.hpp"
#include "../../hardware_interfaces/serial/chat.hpp"
#include "../../hardware_interfaces/gpio/rpi_gpio.hpp"

#include "../../tank/tank.h"

#include "logic.hpp"


logic::logic(){
	
	}



void logic::init(){
	steady now = time_now;
	//~ auto end = std::chrono::steady_clock::now();
	//~ std::chrono::duration<double> elapsed_seconds = end - start;
	
	//~ std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	main_rotation.angle = pi_const / 2;
	#ifdef __arm__
	// RaspberryPi specific code
	// set pins as outputs
	// set pins as outputs
	printf("Why yes it is, thank you\n");
	#endif
	main_serial = serial(variables::chat::port, 57600);
	try{
		main_serial.open();
		//~ for(uint16_t i = 0; i < 32768; i++)
		main_serial.write(std::vector<uint8_t>({'D', 'U'}));
		//~ main_serial.close();
		} catch (mn::CppLinuxSerial::Exception e) {
			std::cout << "Would you mind connecting some spare\n serial interface on "<< 
				variables::chat::port <<", you dimwitt?" << std::endl;
			return;
			}
	std::cout << variables::chat::port << std::endl;
	main_camera.init();
	
	/// TODO: make it work better than setting a single value, by reading the line sensors
	steady end = time_now;
	std::chrono::duration<decimal_n> elapsed_seconds = end - now;
	printf("Logic inited in %f s.\n", elapsed_seconds.count());
	while(flags.mode != START_MOVING){
		flags.mode = (std::cin.get() == 'e')? START_MOVING: flags.mode;
		}
	mainloop();
	}




void logic::mainloop(){
	while(1){
		auto start = time_now;
		
		read();
		decide();
		}
	}



void logic::read(steady now){
	main_camera.run(now);
	main_chat.run(now);
	steady next = now;
	std::cout << "IN WAITING: " << main_serial.in_waiting() << std::endl;
	main_serial.write(std::vector<uint8_t>({'D', 'U'}));
	while(std::chrono::duration<decimal_n> (next - now).count() < 10)
		next = time_now;
	main_serial.write(std::vector<uint8_t>({'D', 'U'}));
	main_serial.write(std::vector<uint8_t>({'D', 'U', 'U'}));
	std::cout << "IN WAITING: " << main_serial.in_waiting() << std::endl;
	main_serial.write(std::vector<uint8_t>({'D', 'U'}));
	
	}



void logic::decide(steady now){
	
	}



