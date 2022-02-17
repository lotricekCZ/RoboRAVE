/*
 * rpi_gpio.cpp
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

#ifdef __arm__
	#include <wiringPi.h>
#endif

#include "../../defines/typedefines.h"
#include "rpi_gpio.hpp"


rpi_gpio::rpi_gpio(){
	
	}



void rpi_gpio::init(){
	#ifdef __arm__
		wiringPiSetup(); // NOTE: This needs root privilege to use
		pinMode(serial_pin, OUTPUT); // WiringPi is quite similar to Wiring on Arduino
	#endif
	}


void rpi_gpio::enable_serial(){
	#ifdef __arm__
		digitalWrite(serial_pin, HIGH); // WiringPi is quite similar to Wiring on Arduino
		last_toggled = time_now;
		while(digitalRead(serial_pin) != HIGH);
	#endif
	}



void rpi_gpio::disable_serial(){
	#ifdef __arm__
		digitalWrite(serial_pin, LOW);
		last_toggled = time_now;
		while(digitalRead(serial_pin) != LOW);
	#endif
	}



bool rpi_gpio::get_state(){
	#ifdef __arm__
	return (digitalRead(serial_pin));
	#endif
	return true;
	}



bool rpi_gpio::run(){
	#ifdef __arm__
		
	#endif
	return true;
	}



