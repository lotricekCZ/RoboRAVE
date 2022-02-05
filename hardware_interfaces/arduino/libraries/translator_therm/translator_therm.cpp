/*
 * translator_therm.cpp
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


#include "translator_therm.hpp"


translator_therm::translator_therm(){
	
	}



void translator_therm::decompose(uint8_t in[16]){
	presets.first_index = presets.current_index =	in[0] >> 6 & 0b11;
	presets.last_index = 	in[0] >> 4 & 0b11;
	main_th_dr -> capture();
	}



bool translator_therm::compose(){
	for(uint8_t i = 0; i < 16; i++){
		data[i] = ((uint8_t)round(main_th_dr -> grid[((i/4) * 2 + (presets.current_index >> 1) & 1) * 8
											+ ((i) % 4) * 2 + (presets.current_index & 1)]) + 47) & 127; 
		// constrain to use 7 bits from -47 to 80 deg C so that msb can carry metadata
		}
	data[0] = ((presets.current_index) & 0b10) 	<< 7;
	data[1] = ((presets.current_index) & 0b1) 	<< 8;
	return presets.last_index == presets.current_index++;
	}
