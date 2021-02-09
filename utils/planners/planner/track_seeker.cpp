/*
 * track_seeker.cpp
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


#include "track_seeker.hpp"
#include <vector>

#ifndef TRACK_SEEKER_CPP
#define TRACK_SEEKER_CPP
track_seeker::track_seeker(){
	
	}

bool track_seeker::not_in(std::vector<step> path_r, coordinates c){
	for(step i: path_r){
		if (i.end == c ||  i.start == c){
			return false;
			}
		}
		return true;
	}

	
#endif // TRACK_SEEKER_CPP
