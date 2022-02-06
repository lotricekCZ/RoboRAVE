/*
 * logic.hpp
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

#include <Wire.h>
#include <AMG88xx.h>

#include "../chat/chat.h"
#include "../chat/chat.h"
#include "../lidar/lidar.cpp"
#include "../translator_therm/translator_therm.cpp"
#include "../translator_lidar/translator_lidar.cpp"




#ifndef LOGIC_HPP
#define LOGIC_HPP

enum add_book: uint8_t {IR = 1, GND = 3, STM = 4, MTR = 2, MSR = 0}; // this should be unified
enum msg_type: uint8_t {CMD = 0, DAT = 1};
enum msg_kind: uint8_t {
			SND_LDR = 		0, /*Send data*/
			SND_THERM = 	1, /*Send data continuously*/
			DND_UND = 		6, /*Didn't understand*/
			}; 

class logic {
	public:
		Adafruit_AMG88xx 	*main_thermocam;
		lidar 				*main_lidar;
		chat 				*main_chat;
		translator_lidar	*main_translator_lidar;
		translator_therm	*main_translator_therm;
		
		logic();
		//~ uint8_t
		uint8_t internal_serial_buf[msg_std::length];
		uint32_t write_ser_time = micros();
		uint32_t last_sent_time = micros();
		uint32_t last_sent = millis();
		struct {
			unsigned is_unapplied:1;
			unsigned is_unsent:1;
			unsigned is_pending:1;
			unsigned was_start:1;
			unsigned counts:1;
			unsigned has_data_lidar:1;
			unsigned has_data_therm:1;
			unsigned has_therm:1;
			} flags;
		uint8_t index = 0;
		void write_ser(enum msg_kind, enum add_book);
		void write_ser();
		void decide();
		//rozhodovaci protokol vyhodnocujici hodnotu vstupni zpravy a odpovedi, rozhoduje za motory
		void read();
	protected:
		void decide_kind();
		void decide_sender();
		void decide_type();
	
	
	
	private:
		/* add your private declarations */
};

#endif /* LOGIC_HPP */ 
