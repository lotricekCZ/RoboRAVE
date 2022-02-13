/*
 * translator_lidar.cpp
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


#include "translator_lidar.hpp"


translator_lidar::translator_lidar(){
	presets.tolerable_age = 2048 >> 7;
	}
	


void translator_lidar::decompose(uint8_t in[16]){
	presets.first_index = presets.current_index =	in[0] << 1 | in[1] >> 7;
	presets.last_index =	in[1] << 2 | in[2] >> 6;
	presets.span = 	15 & (in[2] >> 2);
	presets.tolerable_age = in[2] << 7 | in[3] >> 1;
	}



bool translator_lidar::compose(){
	if(presets.span == 0) presets.span = 4;
	uint8_t i;
	uint32_t tol_ext = presets.tolerable_age << 7;
	bool overpassed = false;
	uint32_t now = millis();
	for(i = 0; (i < 3) & !overpassed; i++){
		uint16_t before = presets.current_index;
		presets.current_index += i * presets.span;
		
		if(before < presets.last_index ^ presets.current_index < presets.last_index){ // means last got overpassed
			presets.current_index = presets.last_index;
			overpassed = true;
			}
		presets.current_index %= 360;
		for(uint8_t find = 0; find < 255; find++){
			int16_t plus = (presets.current_index + find) % 360;
			int16_t minus = (presets.current_index - find);
			minus = ((minus) < 0? (360 + minus): minus);
			perimeter::value *p = &main_lidar -> _perimeter.view.at(plus);
			perimeter::value *m = &main_lidar -> _perimeter.view.at(minus);
			uint32_t age_m = (now - m -> last_replaced), age_p = (now - p -> last_replaced);
			if(age_m < tol_ext){
				uint8_t cin = i * 5;
				data[1 + cin] = (m -> distance >> 5);
				data[2 + cin] = (m -> distance << 8) | (m -> angle >> 6);
				data[3 + cin] = (m -> angle << 2) | (3 & (age_m >> 14));
				data[4 + cin] = (age_m >> 6);
				data[5 + cin] = (age_m << 2);
				}
				
			if(age_p < tol_ext){
				uint8_t cin = i * 5;
				data[1 + cin] = (p -> distance >> 5);
				data[2 + cin] = (p -> distance << 8) | (p -> angle >> 6);
				data[3 + cin] = (p -> angle << 2) | (3 & (age_p >> 14));
				data[4 + cin] = (age_p >> 6);
				data[5 + cin] = (age_p << 2);
				}
			}
		}
	return overpassed;
	}



