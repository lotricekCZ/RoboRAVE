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

// hradware peripherals
#include "../../hardware_interfaces/fire_sensors/fire_sensor.hpp"
#include "../../hardware_interfaces/lidar/lidar.hpp"

#include "../../tank/tank.h"

#include "logic.hpp"


logic::logic(){
	
	}



void logic::init(){
	steady now = time_now;
	//~ auto end = std::chrono::steady_clock::now();
	//~ std::chrono::duration<double> elapsed_seconds = end - start;
	
	//~ std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	
	//~ main_path_wrapper = path_wrapper(path(step(coordinates(-3, -6), coordinates(6, 7))));
	
	main_rotation.angle = pi_const / 2;
	
	main_fire_sensor = 		fire_sensor(main_chat);
	main_ground_sensor = 	ground_sensor(main_chat);
	main_lidar = 			lidar(main_chat);
	main_motors = 			motors(main_chat);
	#ifdef __arm__
		// RaspberryPi specific code
		// set pins as outputs
		// set pins as outputs
		main_serial = serial(variables::chat::port, 115200);	
	#else
		main_serial = serial(variables::chat::port, 57600);	
	#endif
	
	main_camera.init();
	main_gpio.init();
	main_chat.init(main_serial, main_gpio);
	try{
		main_serial.open();
		//~ for(uint16_t i = 0; i < 32768; i++)
		//~ main_serial.write(std::vector<uint8_t>({'D', 'U'}));
		//~ main_serial.close();
		} catch (mn::CppLinuxSerial::Exception e) {
			std::cout << "Would you mind connecting some spare\n serial interface on "<< 
				variables::chat::port << ", you dimwitt?" << std::endl;
			return;
			}
	
	main_fire_sensor.question();
	main_ground_sensor.question();
	/// TODO: make it work better than setting a single value, by reading the line sensors
	steady end = time_now;
	std::chrono::duration<decimal_n> elapsed_seconds = end - now;
	printf("Logic inited in %f s.\n", elapsed_seconds.count());
	std::this_thread::sleep_for(std::chrono::milliseconds(75));
	while(flags.mode != START_MOVING && std::chrono::duration<decimal_n>(time_now - end).count() > 1.0f){
		//~ flags.mode = (std::cin.get() == 'e')? START_MOVING: flags.mode;
		main_ground_sensor.question();
		flags.mode = START_MOVING;
		}
	mainloop();
	}




void logic::mainloop(){
	while(1){
		auto start = time_now;
		read(start);
		apply(start);
		decide(start);
		}
	}



void logic::read(steady now){
	if(std::chrono::duration<decimal_n>(now - test).count() >= 0.25){
		//~ main_ground_sensor.question();
		test = now;
		}
	//~ std::cout << "IN WAITING: " << main_serial.in_waiting() << std::endl;
	//~ std::vector<uint8_t> grabbed(main_serial.in_waiting());
	
	main_camera.run(now);
	main_chat.run(now);
	steady next = now;
	
	//~ main_serial.write(std::vector<uint8_t>({'D', 'U', 69}));
	//~ while(std::chrono::duration<decimal_n> (next - now).count() < 0.1f)
		//~ next = time_now;
	//~ std::cout << "PASS" << std::endl;
	//~ main_serial.write(std::vector<uint8_t>({'D', 'U', 'K', 'E', 'B', 'A', 'B'}));
	
	}



void logic::decide(steady now){
	
	}



void logic::apply(steady now){
	//~ std::cout << main_path_wrapper.has_next() << std::endl;
	if(main_path_wrapper.has_next()){
		//~ printf("HAS TIME %d\n\n\n", main_path_wrapper.its_time(now));
		if(main_path_wrapper.its_time(now)){
			//~ printf("HAS NEXT\n\n\n");
			auto app = main_path_wrapper.translate();
			if(main_motors.queue < 10){
				main_path_wrapper.head++;
				main_motors.assign(app.second, app.first);
				main_motors.question();
				}
			if(!main_path_wrapper.has_next()) std::cout << "NOPE\n\n" << std::endl;
			}
		}
	}



void logic::fill(fire_sensor *p){
	for(uint8_t i = 0; i < p -> sensors.size(); i++){
		unsigned_b current = p -> sensors.at(i).intensity;
		unsigned_b next = p -> sensors.at((i + 1) % p -> sensors.size()).intensity;
		for(uint8_t j = 0; j < (unsigned_b)p -> spread; j++){
			main_angles.at(i * (unsigned_b)p -> spread + j).intensity = (((current * ((unsigned_b)p -> spread - j)) + next * j) 
																		/ (unsigned_b)p -> spread);
			}
		}
	p -> has_data = false;
	}



void logic::fill(ground_sensor *p){
	/*
	 for(auto o: p -> sensors){
		main_angles.at((unsigned_n)o.angle) = o.intensity;
		main_angles.at(((unsigned_n)o.angle + 1) % 360) = o.intensity;
		main_angles.at(((unsigned_n)o.angle < 1) * 360 + (unsigned_n)o.angle - 1) = o.intensity;
		} */
	// there is no structure to hold the ground sensor data
	p -> has_data = false;
	}



void logic::fill(lidar *p){
	// it is important to backtrack the step to import anything to a map
	while(p -> conv_vals.size()){
		auto back = p -> conv_vals.back();
		node backtracked = main_path_wrapper.backtrack(back.time); // find where it was this much time ago.
		p -> conv_vals.erase(p -> conv_vals.end());
		}
	}



void logic::fill(thermocam *p){
	
	}


