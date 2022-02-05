/*
 * perimeter.cpp
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


#include "perimeter.hpp"


perimeter::perimeter(){
	}



perimeter::value::value(uint16_t distance, uint8_t quality, uint64_t time, uint16_t angle){
	this -> distance = distance;
	this -> quality = quality;
	this -> last_replaced = time;
	this -> angle = (angle <= 359)? angle: 0;
	}



bool perimeter::replace(perimeter::value v){
	perimeter::value *c = &this -> view.at(v.angle);
	if(v.quality != 0){
		if(c -> quality < v.quality || ((c -> last_replaced + replace_time) < v.last_replaced)){
			this -> view.at(v.angle) = v;
			return true;
			}
		}
	return false;
	}



bool perimeter::replace(uint16_t distance, uint8_t quality, uint64_t time, uint16_t angle){
	//~ Serial2.print("ANGLE: ");
	//~ Serial2.print(511 & angle);
	//~ Serial2.print(" distance: ");
	//~ Serial2.print(8191 & distance);
	//~ Serial2.print(" quality: ");
	//~ Serial2.print(255 & quality);
	//~ Serial2.print(" time: ");
	//~ Serial2.println(time);
	return this -> replace(perimeter::value(distance, quality, time, angle));
	}
