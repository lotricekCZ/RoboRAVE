/*
 * logic.hpp
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


#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "../../hardware_interfaces/serial/chat.hpp"
#include "../../hardware_interfaces/object_recognition/camera.hpp"
#include "../../hardware_interfaces/fire_sensors/fire_sensor.hpp"
#include "../../hardware_interfaces/ground_sensors/ground_sensor.hpp"
#include "../../hardware_interfaces/lidar/lidar.hpp"
#include "../../hardware_interfaces/gpio/rpi_gpio.hpp"
#include "../../hardware_interfaces/turbine/turbine.hpp"
#include "path_wrapper.hpp"

#include <memory>

enum flow_modes: uint8_t { // flow modes of program, affected by user input buttons
	ERROR			= 0,
	INITIALISING	= 1,
	AWAIT_LAUNCH	= 2,
	START_MOVING	= 3,
	ABORT_PROGRAM	= 4,
	AWAIT_REINIT	= 5
	};


enum path_modes: uint8_t {
	SEARCHING		= 0, // looks for potential places, creates path to unexplored places
	HUNTING			= 1, /* knows of a candle, goes for it, still seeks for anothers, 
	but changes path only if an obstacle appears on the track */
	};

class logic {
	// properties of a vehicle
	node 		main_rotation; 
	speeds 		main_speeds;	
	tank 		main_tank;
	location 	main_location;
	camera	 	main_camera;
	
	
	// hardware peripheries
	//~ camera	 	main_camera;
	serial		main_serial;
	chat	 	main_chat;
	ground_sensor	main_ground_sensor;
	fire_sensor	main_fire_sensor;
	lidar		main_lidar;
	turbine		main_turbine;
	motors		main_motors;
	rpi_gpio	main_gpio;
	path_wrapper main_path_wrapper = path_wrapper(path(step(coordinates(-3, -6), coordinates(6, 7))));
	
	//~ auto start = std::chrono::steady_clock::now();
	// map & planning stuff
	map 		main_map;
	planner		main_planner;
	angles		main_angles;
	struct {
		flow_modes mode = flow_modes::INITIALISING;
		path_modes mode_hunt = path_modes::SEARCHING;
		} flags;
		
	
	public:
		
		logic();
		void init();
		void mainloop();
		void decide(steady now = time_now);
		void read(steady now = time_now);
		void apply(steady now = time_now); // applies data gained from peripherals
		steady test = time_now;
	private:
		/* add your private declarations */
};

#endif /* LOGIC_HPP */ 
