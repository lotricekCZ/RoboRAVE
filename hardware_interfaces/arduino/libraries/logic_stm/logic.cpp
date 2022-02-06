/*
 * logic.cpp
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


#include <Arduino.h>
#include <Wire.h>
#include "logic.hpp"


logic::logic(){
	
	}




void logic::read(){
//Serial.println("N/A");
	if(Serial.available() != 0){ // read if there is something to read
		uint8_t read = Serial.read();
		internal_serial_buf[index] = read;
	    uint8_t ri = index + 1;
	    ri = (ri < msg_std::length? ri: 0);
		if(internal_serial_buf[index] == msg_std::end){
			if(internal_serial_buf[ri] == msg_std::start){				
				for(uint8_t i = ri; i < msg_std::length; i++){
					main_chat -> buffer[i - ri] = internal_serial_buf[i];
					} // copy them with an offset of sth
				for(uint8_t i = 0; i < ri; i++){
					main_chat -> buffer[i] = internal_serial_buf[ri + i];
					} // copy them with an offset of sth
				if(!main_chat -> debufferize(main_chat -> buffer)){
					// executed if the message was not understood
					main_chat -> clear_message();
					main_chat -> outcoming.kind = DND_UND;
					main_chat -> outcoming.type = CMD;
					main_chat -> bufferize();
					for(uint8_t i = 0; i < msg_std::length; i++){
						Serial.write(main_chat -> buffer[i]);
						}
					Serial.flush();
					return;
					}
				flags.is_unapplied = true;			
				}
			}
		index = ri;
		}
		
	/*
	if(Wire.available() > 20){
		main_chat -> clear_message();
		Wire.readBytes(main_chat -> buffer, msg_std::length);
		main_chat -> debufferize(main_chat -> buffer);
		if(!main_chat -> debufferize(main_chat -> buffer)){
			main_chat -> outcoming.kind = DND_UND;
			main_chat -> outcoming.type = CMD;
			return;
			}
		flags.is_unapplied = true;
		}
		*/
		
	
	
	}



void logic::decide(){
	uint32_t cooldown = micros();
	uint32_t cd = millis();
	if((last_sent + 4000) < cd){
		flags.has_data_therm = 1;
		uint8_t decos[16];
		decos[0] = 48;
		main_translator_therm -> decompose(decos);
		last_sent = cd;
		}
	
	if(flags.is_unapplied){
		switch((main_chat -> incoming.receiver)){
			// Serial.println("\nDEC\n");
			case STM:
				// Serial.println("\nDEC->SEN\n");
				decide_sender();
				break;
			default:
				break;
			}
		flags.is_unapplied = false;
		}
	
	// if there is nothing in send state and also if they had enough time to say something
	if(!flags.is_unsent && ((last_sent_time + INTER_DELAY) < cooldown)){
		// look if any of them have something
		if(flags.has_data_therm){
			flags.has_data_therm = main_translator_therm -> compose();
			main_chat -> fill_message(main_translator_therm -> data);
			Serial2.println("HAS DATA?");
			for(uint8_t i = 0; i < 16; i++)
				Serial2.print(main_chat -> buffer[i]);
			Serial2.println();
			for(uint8_t i = 0; i < 16; i++)
				Serial2.print(main_translator_therm -> data[i]);
			write_ser(SND_THERM, MSR);
			}
		/*
		if(flags.has_data_lidar){
			flags.has_data_lidar = main_translator_lidar -> compose();
			main_chat -> fill_message(main_translator_lidar -> data);
			write_ser(SND_LDR, MSR);
			}*/
		}
		
	if(flags.is_unsent){
		if(write_ser_time + COOLDOWN < cooldown){
			write_ser();
			write_ser_time = cooldown;
			}
		}
		
	
	if(flags.is_pending){
		if(write_ser_time + COOLDOWN < cooldown){
			digitalWrite(RS_enable, 0);
			last_sent_time = cooldown;
			flags.is_unapplied = 0;
			flags.is_pending = 0;
			flags.is_unsent = 0;
			}
		}
	}



void logic::decide_sender(){
	switch(main_chat -> incoming.sender){
		case MSR:
			// Serial.println("\nSEN->TYP\n");
			decide_type();
			break;
		default:
			return;
		}
	}



void logic::decide_kind(){
		//Serial.println("Ki");
	switch(main_chat -> incoming.kind){
		case SND_LDR:
			//Serial.println("\n\nSET_MOT\n\n");
			//~ main_translator_lidar -> fill_input(main_chat -> incoming.message_space);
			main_translator_lidar -> decompose(main_chat -> incoming.message_space);
			//~ main_translator_lidar -> apply(main_lidar);
			flags.has_data_lidar = 1;
			break;
		
		case SND_THERM:
			//~ main_translator_therm -> fill_input(main_chat -> incoming.message_space);
			main_translator_therm -> decompose(main_chat -> incoming.message_space);
			flags.has_data_therm = 1;
			break;
		}
	}	



void logic::decide_type(){
	switch(main_chat -> incoming.type){
		// Serial.println("\nTYP\n");
		case CMD:
			// Serial.println("\nTYP->KIN\n");
			decide_kind();
			break;
		case DAT:
			return;
		}
	}	


	
void logic::write_ser(enum msg_kind datatype, enum add_book rec){
	main_chat -> outcoming.kind = datatype;
	main_chat -> outcoming.sender = STM;
	main_chat -> outcoming.receiver = rec;
	main_chat -> outcoming.message_number = main_chat -> incoming.message_number + 1;
	main_chat -> outcoming.type = DAT;
	main_chat -> bufferize();
	if(!flags.is_unsent){
		digitalWrite(RS_enable, 1); // That is the RS485 chip leg (I guess)
		write_ser_time = micros();
		flags.is_unsent = 1;
		return;
		}
	for(uint8_t i = 0; i < msg_std::length; i++){
		Serial2.write(main_chat -> buffer[i]);
		}
	flags.is_unsent = 0; // message has been sent
	Serial.flush();
	flags.is_pending = 1;
	write_ser_time = micros();
	}



void logic::write_ser(){
	if(!flags.is_unsent){
		digitalWrite(RS_enable, 1); // That is the RS485 chip leg (I guess)
		write_ser_time = micros();
		flags.is_unsent = 1;
		return;
		}
	main_chat -> bufferize();
	for(uint8_t i = 0; i < msg_std::length; i++){
		Serial2.write(main_chat -> buffer[i]);
		}
	flags.is_unsent = 0;
	Serial.flush();
	flags.is_pending = 1;
	write_ser_time = micros();
	}
	
