/*
 * fire_sensor.cpp
 * 
 * Copyright 2021 Jakub Ramašeuski <jakub@skaryna.net>
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


#include "fire_sensor.hpp"
#include "../../utils/data_containers/angles/node/node.cpp"
#include <vector>

/*
 * 
 * name: fire_sensor
 * @param sensors - number of sensors included
 * @param spread - spread of each sensor 
 * @param range - general range of sensors
 * 
 */

fire_sensor::fire_sensor(uint8_t sensors = 8, decimal_n spread = 45 /*degrees*/, decimal_n range = 70 /*cm*/){
	this -> sensors = std::vector<node> (sensors);
	this -> range = range;
	this -> spread = spread;
}

bool fire_sensor::update(){
	
}
	
std::vector<node> fire_sensor::get_data(bool update = false){
	
}

