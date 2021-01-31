/*
 * planner.cpp
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


#include "planner.hpp"


planner::planner()
{
	
}

circle planner::create_perimeter(coordinates c){
	return circle(c, robot_radius*2.0);
	}

std::vector<step> planner::plan_make(location goal, location start, decimal_n current_angle){
	const uint8_t max = 90;
	bool reached = false;
	uint8_t target = max+1;
	decimal_n distance = start.get_distance(goal);
	decimal_n angle = start.get_angle(goal) - current_angle;
	location temp_loc = start;
	step temp_step;
	std::vector<step> out;
	//~ out.push_back(step());
	decimal_n start_index = (angle / pi) * 180; // get this thing from radians
	while(!reached){
		if(out.size() > 0){
			reached = (out.back().end == goal._coordinates);
			if(reached){
				break;
				}
			}
		/// TODO: These rely much on the static code on the top, make it to not be so
		for(signed_n index = 0; index <= max+1; index++){ // it doesnt have much sense since hitting this barrier, rotation is needed 
			if(sight -> get_angle((round(start_index) + index >= 360 ? -360: 0) + (round(start_index) + index)).get_distance() > distance){
					target = index;
					break;
				}
				
			if(sight -> get_angle((round(start_index) - index < 0 ? 360: 0) + (round(start_index) - index)).get_distance() > distance){
					target = index;
					break;
				}
				
			}
		
		if(target == (max+1)){ // this means it is out of range and there never was a change of value
				
			}else{
				
				}
		}
			
	return out;
	}


std::vector<step> planner::plan_calculate(std::vector<step> in){
	std::vector<step> out = in;
	
	return out;
	}
