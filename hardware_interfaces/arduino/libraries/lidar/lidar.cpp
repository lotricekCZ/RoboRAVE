/*
 * lidar.cpp
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

#include <cmath>

#ifndef LIDAR_CPP
#define LIDAR_CPP

#include "perimeter.cpp"
#include "lidar_standard.hpp"
#include "lidar.hpp"

#define BSWAP16(n) ((n) << 8 | ((n) >> 8 & 0x00FF))



lidar::lidar(){
	this -> baud = ldr_std::baudrate;
	}


/*
bool lidar::parse(uint8_t *bytes[ldr_std::length_packet]){
	lidar::message m = *((lidar::message*) bytes);
	}
*/

bool lidar::read(){ // I copied most of the AVR code in order to boost the process. Modulus is inefficient.
	//~ Serial2.println(__LINE__);
	if(attached -> available() != 0){ // read if there is something to read
		uint8_t read = (uint8_t)attached -> read();
		if(index < ldr_std::length_header){
			if((uint8_t)read == (uint8_t)ldr_std::header[index]){
				buffer[index] = read;
				index++;
				} else index = 0;
			} else {
				attached -> readBytes(&buffer[ldr_std::length_header], ldr_std::length_packet - ldr_std::length_header);
				index = 0;
				return true;
				}
		}
	return false;
	}



bool lidar::parse(){
	//~ Serial2.println(__LINE__);
	//~ Serial2.println();
	
	uint32_t now = millis();
	//~ if(last_checked > now) last_checked = now;
	for(uint8_t i = 0; i < ldr_std::length_header; i++)
		if(ldr_std::header[i] != buffer[i])
			return false;
	//~ Serial2.println("PARSE");
	float start = (float)(buffer[ldr_std::ang_first] | buffer[ldr_std::ang_first + 1] << 8) / ldr_std::angle_div - ldr_std::angle_sub;
	float end 	= (float)(buffer[ldr_std::dist_first + (ldr_std::dist_size + ldr_std::qual_size) * ldr_std::dist_num] 
						| buffer[ldr_std::dist_first + (ldr_std::dist_size + ldr_std::qual_size) * ldr_std::dist_num + 1] << 8)
						/ ldr_std::angle_div - ldr_std::angle_sub;
	if(start >= 360 || start < 0 || end >= 360 || end < 0) return false;
	//~ Serial2.println("START " + String(start));
	//~ Serial2.println("END " + String(end));
	float step 	= (end - start + (end < start) * 360) / (float)ldr_std::dist_num;
	for(uint8_t i = 0; i < ldr_std::dist_num; i++){
		uint8_t dist_ind = ldr_std::dist_first + i * (ldr_std::dist_size + ldr_std::qual_size);
		_perimeter.replace((uint16_t)(buffer[dist_ind] | (buffer[dist_ind + 1] << 8)), 
							((uint8_t)(buffer[dist_ind + 2])),
							now, round(start + i * step));
		}
	/* 
	 * You wrote this nonsense shit, hate yourself. <3 Cry louder.
	 * It converts an address into uint16_t, but because it's been send
	 * as little-endian, you use BSWAP macro. Then you're passing
	 * quality of that measurement.
	*/
	}



bool lidar::parse(uint8_t *bytes[ldr_std::length_packet]){
	for(uint8_t i = 0; i < ldr_std::length_header; i++)
		if(ldr_std::header[i] != *bytes[i]) 
			return false;
	//~ Serial2.println("PARSE");
	uint32_t now = millis();
	float start = BSWAP16(*((uint16_t *)(bytes[ldr_std::ang_first]))) / ldr_std::angle_div - ldr_std::angle_sub;
	float end 	= BSWAP16(*((uint16_t *)(bytes[ldr_std::ang_first + ldr_std::dist_num * (ldr_std::dist_size + ldr_std::qual_size)]))) / ldr_std::angle_div - ldr_std::angle_sub;
	float step 	= (end - start + (end < start) * 360) / (float)ldr_std::dist_num;
	if(start >= 360 || start < 0 || end >= 360 || end < 0) return false;
	for(uint8_t i = 0; i < ldr_std::dist_num; i++)
		_perimeter.replace(BSWAP16(*((uint16_t *)(bytes[ldr_std::dist_first 
								+ i * (ldr_std::dist_size + ldr_std::qual_size)]))), 
							*((uint8_t *)(bytes[ldr_std::dist_size + ldr_std::dist_first 
								+ i * (ldr_std::dist_size + ldr_std::qual_size)])),
							now, round(start + i * step));
	/* 
	 * You wrote this nonsense shit, hate yourself. <3 Cry louder.
	 * It converts an address into uint16_t, but because it's been send
	 * as little-endian, you use BSWAP macro. Then you're passing
	 * quality of that measurement.
	*/
	return true;
	}


void lidar::attach(HardwareSerial *port){
	this -> attached -> end();
	this -> attached = port;
	if(!(*port))
		this -> attached -> begin(ldr_std::baudrate, SERIAL_8N1);
	}


lidar::loop_ret lidar::handle_in_background(){
	//~ Serial2.println(__LINE__);
	//~ Serial2.println("Packet received");
	uint8_t ret = 0;
	static uint32_t last_checked;
	if(!(*attached)){
		//~ Serial2.println(__LINE__);
		this -> attached -> begin(ldr_std::baudrate, SERIAL_8N1);
		}
	if(read()) ret = loop_ret::NEW_PACKET | loop_ret::FAIL * (!parse());
	if(ret & loop_ret::NEW_PACKET == loop_ret::NEW_PACKET){
		//~ Serial2.println("Packet received");
		
		uint16_t valid = 0;
		uint32_t now = millis();
		if(last_checked > now) last_checked = now;
		if(last_checked + 500 < now){
			for(uint16_t i = 0; i < 360; i++){
				if(_perimeter.view.at(i).distance != 0){
					//~ Serial2.print("\t");
					//~ Serial2.print(_perimeter.view.at(i).angle);
					//~ Serial2.print("\t");
					//~ Serial2.print(String((float)_perimeter.view.at(i).distance / 10.0));
					
					valid += ((_perimeter.view.at(i).last_replaced) > last_checked);
						//~ valid++;
						//~ Serial2.print("\t<- VALID");
						
					//~ Serial2.println();
					}
				}
			//~ Serial2.print("VALID: ");
			Serial2.println(valid);
			last_checked = now;
			//~ */
			}
		}
	return (lidar::loop_ret)ret;
	}

#endif // LIDAR_CPP
