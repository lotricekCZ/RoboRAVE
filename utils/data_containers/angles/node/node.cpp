/*
 * node.cpp
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


#include "node.hpp"


node::node()
{
	
}
void node::set_distance(decimal_n i){
	distance = i;
	}
	
void node::set_intensity(unsigned_n i){
	intensity = i;
	}
	
void node::set_angle(decimal_n i){
	angle = i;
	}

decimal_n node::get_distance(){
	return distance;
	}
	
unsigned_n node::get_intensity(){
	return intensity;
	}
	
decimal_n node::get_angle(){
	return angle;
	}
node::~node()
{
	
}

