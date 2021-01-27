/*
 * angles.cpp
 * 
 * Copyright 2020 Jakub Ramašeuski <jakub@skaryna.net>
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


#include "angles.hpp"


angles::angles()
	: vector()
{
	for(unsigned_n i = 0; i < 360; i ++){
		push_back(node(0.0f, (decimal_n)i));
		}
	std::sort(this -> begin(), this -> end(), [](node a, node b){return (a.angle < b.angle);});
}

node angles::get_angle(signed_n angle){
	return at(angle);
	}
	
angles::~angles()
{
	
}

// loads the virtual angles on any coordinate on the map... Well at least this is what it should do
angles angles::load_virtual(coordinates a, map &m){
	for(unsigned_n i = 0; i <= 180; i ++){
		line l(a, a.make_local(1, i/180f*pi);
		for(auto& a: m._map_obstacles){
			if(a.is_collision_course(l))
			}
		push_back(node(0.0f, (decimal_n)i));
		}
	std::sort(this -> begin(), this -> end(), [](node a, node b){return (a.angle < b.angle);});
	}

