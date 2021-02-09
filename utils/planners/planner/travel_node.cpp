/*
 * travel_node.cpp
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


#include "travel_node.hpp"

#ifndef TRAVEL_NODE_CPP
#define TRAVEL_NODE_CPP

travel_node::travel_node(unsigned_b id, coordinates coords){
	this -> id = id;
	this -> coords = coords;
	}

std::vector<travel_node> travel_node::convert(std::vector<coordinates>& c){
	std::vector<travel_node> ret;
	for(unsigned_b i = 0; i < c.size(); i++){
		ret.push_back(travel_node(i, (c[i])));
		}
	return ret;
	}
	
#endif // TRAVEL_NODE_CPP